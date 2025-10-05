//
// Created by zoukini on 06/10/2025.
//

#ifndef JSONPARSER_JSONCOMPOSITEIMPL_H
#define JSONPARSER_JSONCOMPOSITEIMPL_H

#include "JsonComposite.hpp"
#include "../../visitor/JsonVisitor.hpp"

inline void JsonArray::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

inline void JsonArray::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}

inline void JsonObject::accept(JsonVisitor& visitor) {
    visitor.visit(*this);
}

inline void JsonObject::accept(JsonVisitor& visitor) const {
    visitor.visit(*this);
}


#endif //JSONPARSER_JSONCOMPOSITEIMPL_H