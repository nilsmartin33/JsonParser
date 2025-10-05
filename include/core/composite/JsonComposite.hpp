//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONCOMPOSITE_HPP
#define JSONPARSER_JSONCOMPOSITE_HPP

#include "../JsonValue.hpp"
#include <vector>
#include <map>
#include <memory>
#include <sstream>

class JsonVisitor;

class JsonArray final : public JsonValue {
public:
    JsonArray() {
        elements.reserve(16);
    };

    [[nodiscard]] JsonType getType() const override { return JsonType::Array; }

    void add(std::unique_ptr<JsonValue> value) {
        elements.push_back(std::move(value));
    }

    [[nodiscard]] const std::vector<std::unique_ptr<JsonValue>>& getElements() const {
        return elements;
    }

    [[nodiscard]] size_t size() const {
        return elements.size();
    }

    [[nodiscard]] bool empty() const {
        return elements.empty();
    }

    [[nodiscard]] const JsonValue* at(const size_t index) const {
        return find(index);
    }

    [[nodiscard]] JsonValue* at(const size_t index) {
        return find(index);
    }

    [[nodiscard]] const JsonValue& operator[](const size_t index) const {
        if (index >= elements.size())
            throw std::out_of_range("JsonArray index out of range: " + std::to_string(index));
        return *elements[index];
    }

    void reserve(const size_t capacity) {
        elements.reserve(capacity);
    }

    [[nodiscard]] std::string toString() const override {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < elements.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << elements[i]->toString();
        }
        oss << "]";
        return oss.str();
    };

    void accept(JsonVisitor& visitor) override;
    void accept(JsonVisitor& visitor) const override;

private:
    std::vector<std::unique_ptr<JsonValue>> elements;

    [[nodiscard]] JsonValue *find(const size_t index) const {
        if (index >= elements.size())
            return nullptr;
        return elements[index].get();
    }
};

class JsonObject final : public JsonValue {
public:
    JsonObject() = default;

    [[nodiscard]] JsonType getType() const override { return JsonType::Object; }

    void set(const std::string& key, std::unique_ptr<JsonValue> value) {
        if (!value)
            throw std::invalid_argument("Cannot set null unique_ptr in JsonObject");
        members[key] = std::move(value);
    };

    [[nodiscard]] const std::map<std::string, std::unique_ptr<JsonValue>>& getMembers() const {
        return members;
    };

    [[nodiscard]] size_t size() const {
        return members.size();
    };

    [[nodiscard]] bool empty() const {
        return members.empty();
    };

    [[nodiscard]] bool has(const std::string &str) const {
        return members.find(str) != members.end();
    };

    [[nodiscard]] const JsonValue* get(const std::string& key) const {
        return find(key);
    };

    [[nodiscard]] JsonValue *get(const std::string &key) {
        return find(key);
    };

    [[nodiscard]] const JsonValue &operator[](const std::string &key) const {
        const auto it = members.find(key);
        if (it == members.end()) {
            throw std::out_of_range("JsonObject key not found: " + key);
        }
        return *it->second;
    };

    [[nodiscard]] std::string toString() const override {
        std::ostringstream oss;
        oss << "{";
        bool first = true;
        for (const auto& [key, value] : members) {
            if (!first) oss << ", ";
            first = false;
            oss << "\"" << key << "\": " << value->toString();
        }
        oss << "}";
        return oss.str();
    };

    void accept(JsonVisitor& visitor) override;
    void accept(JsonVisitor& visitor) const override;
private:
    std::map<std::string, std::unique_ptr<JsonValue>> members;

    [[nodiscard]] JsonValue *find(const std::string &key) const {
        const auto it = members.find(key);
        return it == members.end() ? nullptr : it->second.get();
    }
};

#endif //JSONPARSER_JSONCOMPOSITE_HPP