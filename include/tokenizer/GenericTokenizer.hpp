//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_GENERICTOKENIZER_HPP
#define JSONPARSER_GENERICTOKENIZER_HPP

#include "CharStreamReader.hpp"
#include "CharClassifiers.hpp"
#include "ITokenParser.hpp"
#include "ITokenizer.hpp"
#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>

template<typename TokenType>
class GenericTokenizer : public ITokenizer<TokenType> {
public:
    using TokenFactory = std::function<TokenType(CharStreamReader&)>;

    explicit GenericTokenizer(const std::string_view input) : reader{input} {
        parsers.reserve(32);
    };

    ~GenericTokenizer() override = default;

    GenericTokenizer(const GenericTokenizer&) = delete;
    GenericTokenizer& operator=(const GenericTokenizer&) = delete;
    GenericTokenizer(GenericTokenizer&&) = delete;
    GenericTokenizer& operator=(GenericTokenizer&&) = delete;

    void registerFactory(char key, TokenFactory factory) {
        factories[key] = std::move(factory);
    };

    template<typename T>
    void registerParser(char key, std::unique_ptr<T> parser) {
        std::size_t index = parsers.size();
        parsers.emplace_back(std::move(parser));

        factories[key] = [this, index](CharStreamReader &r) {
            return static_cast<T*>(parsers[index].get())->parse(r);
        };
    };

    template<typename T>
    void registerParserForKeys(const std::vector<char>& keys, std::unique_ptr<T> parser) {
        std::size_t index = parsers.size();
        parsers.emplace_back(std::move(parser));

        TokenFactory factory = [this, index](CharStreamReader& r) {
            return static_cast<T*>(parsers[index].get())->parse(r);
        };

        for (char key : keys) {
            factories[key] = factory;
        }
    }

    template<typename T>
    T* getLastParser() {
        if (parsers.empty())
            return nullptr;
        return dynamic_cast<T*>(parsers.back().get());
    };

    std::vector<TokenType> tokenize() override {
        std::vector<TokenType> tokens;
        tokens.reserve(256);
        while (reader.hasNext()) {
            skipWhitespace();
            if (!reader.hasNext()) break;
            char c = reader.peek();
            tokens.push_back(parseToken(c));
        }
        return tokens;
    };

    [[nodiscard]] std::size_t currentLine() const override { return reader.getLine(); };
    [[nodiscard]] std::size_t currentColumn() const override { return reader.getColumn(); };

protected:
    CharStreamReader reader;
    std::unordered_map<char, TokenFactory> factories;
    std::vector<std::unique_ptr<ITokenParser<TokenType>>> parsers;

private:
    virtual void skipWhitespace() {
        using namespace CharClassifiers;
        reader.skipWhile(isSpace);
    };

    virtual TokenType parseToken(char c) {
        auto it = factories.find(c);
        if (it != factories.end())
            return it->second(reader);
        return createErrorToken(c);
    };

    virtual TokenType createErrorToken(char c) = 0;
};

#endif //JSONPARSER_GENERICTOKENIZER_HPP