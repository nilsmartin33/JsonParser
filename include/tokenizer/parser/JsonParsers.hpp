//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONPARSERS_HPP
#define JSONPARSER_JSONPARSERS_HPP

#include "CharClassifiers.hpp"
#include "ITokenParser.hpp"
#include "IToken.hpp"

class JsonNumberParser final : public ITokenParser<JsonToken> {
    public:
        JsonToken parse(CharStreamReader& reader) override {
            JsonToken token{JsonTokenType::NUMBER, "", reader.getLine(), reader.getColumn()};

            using namespace CharClassifiers;

            if (reader.peek() == '-')
                token.value += reader.advance();

            while (isDigit(reader.peek()))
                token.value += reader.advance();

            if (reader.peek() == '.') {
                reader.advance();
                while (isDigit(reader.peek()))
                    token.value += reader.advance();
            }
            return token;
        }
};

class JsonStringParser final : public ITokenParser<JsonToken> {
    public:
        JsonToken parse(CharStreamReader& reader) override {
            JsonToken token{JsonTokenType::STRING, "", reader.getLine(), reader.getColumn()};
            reader.advance();

            char c = reader.peek();
            while (c != '"' && c != '\0') {
                if (c == '\\') {
                    reader.advance();
                    const char escaped = parseEscape(reader.advance());
                    if (escaped == '\0') {
                        token.type = JsonTokenType::ERROR;
                        return token;
                    }
                    token.value += escaped;
                } else {
                    token.value += c;
                    reader.advance();
                }
                c = reader.peek();
            }
            if (c == '"')
                reader.advance();
            else
                token.type = JsonTokenType::ERROR;
            return token;
        }
    private:
        static char parseEscape(const char escaped) {
            switch (escaped) {
                case '"':  return '"';
                case '\\': return '\\';
                case '/':  return '/';
                case 'b':  return '\b';
                case 'f':  return '\f';
                case 'n':  return '\n';
                case 'r':  return '\r';
                case 't':  return '\t';
                default:   return '\0';
            }
        };
};

class JsonKeywordParser final : public ITokenParser<JsonToken> {
    public:
        JsonToken parse(CharStreamReader& reader) override {
            using namespace CharClassifiers;

            JsonToken token{JsonTokenType::ERROR, "", reader.getLine(), reader.getColumn()};

            while (isAlpha(reader.peek())) {
                token.value += reader.advance();
            }

            if (token.value == "true") {
                token.type = JsonTokenType::TRUE;
            } else if (token.value == "false") {
                token.type = JsonTokenType::FALSE;
            } else if (token.value == "null") {
                token.type = JsonTokenType::NULL_TYPE;
            } else {
                token.value = "Unknown keyword: " + token.value;
            }
            return token;
        }
};

#endif //JSONPARSER_JSONPARSERS_HPP