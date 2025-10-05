//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_CHARSTREAMREADER_HPP
#define JSONPARSER_CHARSTREAMREADER_HPP

#include <string_view>

class CharStreamReader {
    public:
        explicit CharStreamReader(std::string_view view)
            : input{view} {};

        [[nodiscard]] bool hasNext() const {
            return pos < input.size();
        }

        [[nodiscard]] char peek() const {
            return hasNext() ? input[pos] : '\0';
        };

        char advance() {
            if (!hasNext())
                return '\0';
            const char c = input[pos++];
            if (c == '\n') {
                line++;
                column = 1;
            } else
                column++;
            return c;
        };

        template<typename Predicate>
        void skipWhile(Predicate p) {
            while (hasNext() && p(peek())) {
                advance();
            }
        };

        [[nodiscard]] std::size_t getPos() const {
            return pos;
        }

        [[nodiscard]] std::size_t getLine() const {
            return line;
        }

        [[nodiscard]] std::size_t getColumn() const {
            return column;
        }

    private:
        std::string_view input;
        std::size_t pos = 0;
        std::size_t line = 1;
        std::size_t column = 1;
};

#endif //JSONPARSER_CHARSTREAMREADER_HPP