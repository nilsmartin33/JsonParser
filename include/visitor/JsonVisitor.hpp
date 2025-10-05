//
// Created by zoukini on 06/10/2025.
//

#ifndef JSONPARSER_JSONVISITOR_HPP
#define JSONPARSER_JSONVISITOR_HPP

#include "core/JsonTypes.hpp"

class JsonNull;
class JsonObject;
class JsonArray;

class JsonVisitor {
    public:
    virtual ~JsonVisitor() = default;

    virtual void visit(const JsonNull &obj) = 0;
    virtual void visit(const JsonObject &obj) = 0;
    virtual void visit(const JsonArray &obj) = 0;

    virtual void visit(const JsonFloat &obj) = 0;
    virtual void visit(const JsonInteger &obj) = 0;
    virtual void visit(const JsonBoolean &obj) = 0;
    virtual void visit(const JsonString &obj) = 0;

};
#endif //JSONPARSER_JSONVISITOR_HPP