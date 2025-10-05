//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONPARSER_HPP
#define JSONPARSER_JSONPARSER_HPP

#include "IParser.hpp"
#include "IToken.hpp"
#include "core/JsonValue.hpp"
#include "core/JsonFactory.hpp"
#include "../core/composite/JsonComposite.hpp"

class JsonParser final : public IParser<JsonToken, JsonValue> {
public:
    explicit JsonParser(std::vector<JsonToken> tokens) : IParser(std::move(tokens)) {
        initStrategies();
    };
    std::unique_ptr<JsonValue> parse() override {
        if (!hasMore() || current().type == JsonTokenType::EOF_TYPE)
            throw std::runtime_error("Empty JSON input");

        auto result = parseValue();

        if (hasMore() && current().type != JsonTokenType::EOF_TYPE)
            throw std::runtime_error("Unexpected tokens after JSON value at line " + std::to_string(current().line));

        return result;
    };
private:
    using ParsingStrategy = std::function<std::unique_ptr<JsonValue>()>;
    std::unordered_map<JsonTokenType, ParsingStrategy> strategies;

    void initStrategies() {
        strategies[JsonTokenType::STRING] = [this]() { return parseString(); };
        strategies[JsonTokenType::NUMBER] = [this]() { return parseNumber(); };
        strategies[JsonTokenType::TRUE] = [this]() { return parseBoolean(); };
        strategies[JsonTokenType::FALSE] = [this]() { return parseBoolean(); };
        strategies[JsonTokenType::NULL_TYPE] = [this]() { return parseNull(); };
        strategies[JsonTokenType::LBRACKET] = [this]() { return parseArray(); };
        strategies[JsonTokenType::LBRACE] = [this]() { return parseObject(); };
    };

    void expect(const JsonTokenType type) {
        if (current().type != type) {
            throw std::runtime_error(
                "Expected " + tokenTypeToString(type) +
                " but got " + tokenTypeToString(current().type) +
                " at line " + std::to_string(current().line)
            );
        }
        advance();
    };

    bool match(const JsonTokenType type) {
        if (!hasMore() || current().type != type)
            return false;
        advance();
        return true;
    }

    std::unique_ptr<JsonValue> parseValue() {
        if (!hasMore())
            throw std::runtime_error("Unexpected end of input");

        const auto it = strategies.find(current().type);
        if (it == strategies.end())
            throw std::runtime_error("Unexpected token: " + tokenTypeToString(current().type) + " at line " + std::to_string(current().line));

        return it->second();
    };

    std::unique_ptr<JsonValue> parseString() {
        auto value = json::make(current().value);
        advance();
        return value;
    };

    std::unique_ptr<JsonValue> parseNumber() {
        const std::string &numStr = current().value;
        advance();
        try {
            if (numStr.find('.') != std::string::npos)
                return json::make(std::stod(numStr));
            return json::make(std::stoll(numStr));
        } catch (const std::exception &e) {
            throw std::runtime_error("Invalid number format: " + numStr + "\nError:" +  e.what());
        }
    };

    std::unique_ptr<JsonValue> parseBoolean() {
        bool value = (current().type == JsonTokenType::TRUE);
        advance();
        return json::make(value);
    };

    std::unique_ptr<JsonValue> parseNull() {
        advance();
        return json::null();
    };

    std::unique_ptr<JsonValue> parseArray() {
        expect(JsonTokenType::LBRACKET);
        auto array = json::array();

        if (match(JsonTokenType::RBRACKET))
            return array;

        array->add(parseValue());
        while (match(JsonTokenType::COMMA))
            array->add(parseValue());

        expect(JsonTokenType::RBRACKET);
        return array;
    };

    std::unique_ptr<JsonValue> parseObject() {
        expect(JsonTokenType::LBRACE);
        auto object = json::object();

        if (match(JsonTokenType::RBRACE))
            return object;

        if (current().type != JsonTokenType::STRING)
            throw std::runtime_error("Expected string key in object at line " + std::to_string(current().line));

        std::string key = current().value;
        advance();
        expect(JsonTokenType::COLON);
        object->set(key, parseValue());

        while (match(JsonTokenType::COMMA)) {
            if (current().type != JsonTokenType::STRING)
                throw std::runtime_error("Expected string key in object at line " + std::to_string(current().line));

            key = current().value;
            advance();
            expect(JsonTokenType::COLON);
            object->set(key, parseValue());
        }

        expect(JsonTokenType::RBRACE);
        return object;
    };

};

#endif //JSONPARSER_JSONPARSER_HPP