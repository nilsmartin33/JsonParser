//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONVALUE_HPP
#define JSONPARSER_JSONVALUE_HPP

#include <string>
#include <iostream>

enum class JsonType {
    Boolean,
    Int,
    Float,
    String,
    Null,
    Array,
    Object
};

class JsonVisitor;

class JsonValue {
public:
    virtual ~JsonValue() = default;

    JsonValue(const JsonValue &) = delete;
    JsonValue& operator=(const JsonValue &) = delete;

    JsonValue(JsonValue &&) = default;
    JsonValue& operator=(JsonValue &&) = default;

    void print() const { std::cout << toString() << std::endl; };

    [[nodiscard]] virtual JsonType getType() const = 0;
    [[nodiscard]] virtual std::string toString() const = 0;

    virtual void accept(JsonVisitor& visitor) = 0;
    virtual void accept(JsonVisitor& visitor) const = 0;
protected:
    JsonValue() = default;
};


#endif //JSONPARSER_JSONVALUE_HPP