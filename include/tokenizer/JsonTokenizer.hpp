//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONTOKENIZER_HPP
#define JSONPARSER_JSONTOKENIZER_HPP

#include "GenericTokenizer.hpp"
#include "ITokenizer.hpp"
#include "IToken.hpp"
#include "JsonParsers.hpp"
#include "JsonTokenizerConfig.hpp"

class JsonTokenizer final : public GenericTokenizer<JsonToken> {
    public:
        explicit JsonTokenizer(std::string_view const json)
            : GenericTokenizer(json) {
            JsonTokenizerConfig::configure(*this);
        };

        std::vector<JsonToken> tokenize() override {
            auto tokens = GenericTokenizer::tokenize();
            tokens.push_back({JsonTokenType::EOF_TYPE, "", reader.getLine(), reader.getColumn()});
            return tokens;
        };

    private:
        JsonToken createErrorToken(char const c) override {
            JsonToken token{JsonTokenType::ERROR, std::string(1, c), reader.getLine(), reader.getColumn()};
            reader.advance();
            return token;
        }
};

#endif //JSONPARSER_JSONTOKENIZER_HPP