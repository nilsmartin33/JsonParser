//
// Created by zoukini on 06/10/2025.
//

#ifndef JSONPARSER_JSONTYPES_HPP
#define JSONPARSER_JSONTYPES_HPP

#include <string>

template<typename T> class JsonPrimitive;

using JsonBoolean = JsonPrimitive<bool>;
using JsonInteger = JsonPrimitive<int64_t>;
using JsonFloat = JsonPrimitive<double>;
using JsonString = JsonPrimitive<std::string>;


#endif //JSONPARSER_JSONTYPES_HPP