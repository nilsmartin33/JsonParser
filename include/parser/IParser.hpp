//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_IPARSER_HPP
#define JSONPARSER_IPARSER_HPP
#include <memory>
#include <vector>

template<typename TokenType, typename ASTNodeType>
class IParser {
    public:
        virtual ~IParser() = default;

        explicit IParser(std::vector<TokenType> input) : tokens(std::move(input)), pos(0) {};
        virtual std::unique_ptr<ASTNodeType> parse() = 0;

        [[nodiscard]] std::size_t getPos() const { return pos; }
        [[nodiscard]] std::size_t getSize() const { return tokens.size(); }

    protected:
        std::vector<TokenType> tokens;
        size_t pos;

    [[nodiscard]] bool hasMore() const {
        return pos < tokens.size();
    }

    const TokenType& current() const {
        if (!hasMore())
            throw std::runtime_error("Unexpected end of tokens");
        return tokens[pos];
    }

    const TokenType& peek(const std::size_t offset = 0) const {
        std::size_t idx = pos + offset;
        if (idx >= tokens.size())
            throw std::runtime_error("Peek out of bounds");
        return tokens[idx];
    }

    void advance() {
        if (hasMore())
            ++pos;
    }

    void advance(const std::size_t count) {
        pos += count;
        if (pos > tokens.size())
            pos = tokens.size();
    }

};

#endif //JSONPARSER_IPARSER_HPP