//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_ITOKENIZER_H
#define JSONPARSER_ITOKENIZER_H

#include <iostream>
#include <vector>

template<typename T>
class ITokenizer {
    public:
        virtual ~ITokenizer() = default;

        virtual std::vector<T> tokenize() = 0;

        [[nodiscard]] virtual std::size_t currentLine() const = 0;
        [[nodiscard]] virtual std::size_t currentColumn() const = 0;
};

#endif // JSONPARSER_ITOKENIZER_H