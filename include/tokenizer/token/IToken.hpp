//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_ITOKEN_HPP
#define JSONPARSER_ITOKEN_HPP

#include <string>
#include <cstddef>

template<typename TokenTypeEnum>
struct GenericToken {
    TokenTypeEnum type;
    std::string value;
    std::size_t line{};
    std::size_t column{};
};

enum class JsonTokenType {
    LBRACE, RBRACE, LBRACKET, RBRACKET,
    COLON, COMMA, STRING, NUMBER,
    TRUE, FALSE, NULL_TYPE, EOF_TYPE, ERROR
};

using JsonToken = GenericToken<JsonTokenType>;

inline std::string tokenTypeToString(JsonTokenType type) {
    static const char* names[] = {
        "LBRACE", "RBRACE", "LBRACKET", "RBRACKET", "COLON", "COMMA",
        "STRING", "NUMBER", "TRUE", "FALSE", "NULL_TYPE", "EOF_TYPE", "ERROR"
    };
    return names[static_cast<int>(type)];
}

#endif //JSONPARSER_ITOKEN_HPP