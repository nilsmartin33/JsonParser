#ifndef JSON_PRIMITIVE_HPP
#define JSON_PRIMITIVE_HPP

#include <string>
#include <sstream>
#include "../JsonValue.hpp"
#include "../JsonTypes.hpp"
#include <type_traits>

class JsonVisitor;

template<typename T>
struct JsonTypeTraits;

template<>
struct JsonTypeTraits<std::string> {
    static constexpr auto type = JsonType::String;
};

template<>
struct JsonTypeTraits<bool> {
    static constexpr auto type = JsonType::Boolean;
};

template<>
struct JsonTypeTraits<int64_t> {
    static constexpr auto type = JsonType::Int;
};

template<>
struct JsonTypeTraits<double> {
    static constexpr auto type = JsonType::Float;
};

class JsonNull final : public JsonValue {
public:
    [[nodiscard]] JsonType getType() const override { return JsonType::Null; }
    [[nodiscard]] std::string toString() const override { return "null"; }

    void accept(JsonVisitor& visitor) override;
    void accept(JsonVisitor& visitor) const override;
};

template<typename T>
class JsonPrimitive final : public JsonValue {
public:
    explicit JsonPrimitive(T value) : value_(std::move(value)) {}

    [[nodiscard]] JsonType getType() const override { return JsonTypeTraits<T>::type; }

    const T& getValue() const { return value_; }

    [[nodiscard]] std::string toString() const override {
        std::ostringstream oss;
        if constexpr(std::is_same_v<T, std::string>)
            oss << "\"" << value_ << "\"";
        else if constexpr (std::is_same_v<T, bool>)
            oss << (value_ ? "true" : "false");
        else
            oss << value_;
        return oss.str();
    }

    void accept(JsonVisitor& visitor) override;
    void accept(JsonVisitor& visitor) const override;

private:
    T value_;
};

#endif