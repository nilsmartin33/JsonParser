//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_CHARCLASSIFIERS_HPP
#define JSONPARSER_CHARCLASSIFIERS_HPP

#include <cctype>

namespace CharClassifiers {
    inline bool isDigit(char c) {
        return std::isdigit(static_cast<unsigned char>(c));
    }

    inline bool isAlpha(char c) {
        return std::isalpha(static_cast<unsigned char>(c));
    }

    inline bool isSpace(char c) {
        return std::isspace(static_cast<unsigned char>(c));
    }

    inline bool isHexDigit(char c) {
        return std::isxdigit(static_cast<unsigned char>(c));
    }

    inline bool isAlphaNum(char c) {
        return std::isalnum(static_cast<unsigned char>(c));
    }
};
#endif //JSONPARSER_CHARCLASSIFIERS_HPP