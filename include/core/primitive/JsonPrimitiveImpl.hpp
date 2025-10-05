//
// Created by zoukini on 06/10/2025.
//
#ifndef JSON_PRIMITIVE_IMPL_HPP
#define JSON_PRIMITIVE_IMPL_HPP

#include "JsonPrimitive.hpp"
#include "../../visitor/JsonVisitor.hpp"

inline void JsonNull::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

inline void JsonNull::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

template<>
inline void JsonBoolean::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

template<>
inline void JsonBoolean::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

template<>
inline void JsonInteger::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

template<>
inline void JsonInteger::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

template<>
inline void JsonFloat::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

template<>
inline void JsonFloat::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

template<>
inline void JsonString::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

template<>
inline void JsonString::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

#endif