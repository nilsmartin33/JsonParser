//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_ITOKENPARSER_HPP
#define JSONPARSER_ITOKENPARSER_HPP

#include "CharStreamReader.hpp"

template<typename TokenType>
class ITokenParser {
public:
    virtual ~ITokenParser() = default;
    virtual TokenType parse(CharStreamReader& reader) = 0;
};

#endif //JSONPARSER_ITOKENPARSER_HPP