//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONTOKENIZERCONFIG_HPP
#define JSONPARSER_JSONTOKENIZERCONFIG_HPP

#include "GenericTokenizer.hpp"
#include "IToken.hpp"
#include "JsonParsers.hpp"
#include <vector>

class JsonTokenizerConfig {
public:
    static void configure(GenericTokenizer<JsonToken>& tokenizer) {
        registerSimpleTokens(tokenizer);
        registerStringParser(tokenizer);
        registerNumberParser(tokenizer);
        registerKeywordParser(tokenizer);
    }

private:
    static void registerSimpleTokens(GenericTokenizer<JsonToken>& tokenizer) {
        registerSimpleToken(tokenizer, '{', JsonTokenType::LBRACE);
        registerSimpleToken(tokenizer, '}', JsonTokenType::RBRACE);
        registerSimpleToken(tokenizer, '[', JsonTokenType::LBRACKET);
        registerSimpleToken(tokenizer, ']', JsonTokenType::RBRACKET);
        registerSimpleToken(tokenizer, ':', JsonTokenType::COLON);
        registerSimpleToken(tokenizer, ',', JsonTokenType::COMMA);
    }

    static void registerSimpleToken(GenericTokenizer<JsonToken>& tokenizer,
                                    char const c, JsonTokenType type) {
        tokenizer.registerFactory(c, [type](CharStreamReader& r) {
            JsonToken token{type, std::string(1, r.peek()), r.getLine(), r.getColumn()};
            r.advance();
            return token;
        });
    }

    static void registerStringParser(GenericTokenizer<JsonToken>& tokenizer) {
        tokenizer.registerParser('"', std::make_unique<JsonStringParser>());
    }

    static void registerNumberParser(GenericTokenizer<JsonToken>& tokenizer) {
        std::vector<char> numberKeys;
        numberKeys.reserve(11);
        numberKeys.push_back('-');

        for (char c = '0'; c <= '9'; ++c) {
            numberKeys.push_back(c);
        }
        tokenizer.registerParserForKeys(numberKeys, std::make_unique<JsonNumberParser>());
    }

    static void registerKeywordParser(GenericTokenizer<JsonToken>& tokenizer) {
        std::vector<char> alphaKeys;
        alphaKeys.reserve(27);
        for (char c = 'a'; c <= 'z'; ++c)
            alphaKeys.push_back(c);
        tokenizer.registerParserForKeys(alphaKeys, std::make_unique<JsonKeywordParser>());
    }
};

#endif //JSONPARSER_JSONTOKENIZERCONFIG_HPP