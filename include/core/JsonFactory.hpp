//
// Created by zoukini on 05/10/2025.
//

#ifndef JSONPARSER_JSONFACTORY_HPP
#define JSONPARSER_JSONFACTORY_HPP

#include "primitive/JsonPrimitive.hpp"
#include "composite/JsonComposite.hpp"
#include <memory>
#include <type_traits>
#include <string>

namespace json {
    template<typename T>
    auto make(T && value) {
        using Type = std::decay_t<T>;

        if constexpr (std::is_same_v<Type, bool>) {
            return std::make_unique<JsonBoolean>(value);
        } else if constexpr (std::is_integral_v<Type> && !std::is_same_v<Type, bool>) {
            return std::make_unique<JsonInteger>(static_cast<int64_t>(value));
        } else if constexpr (std::is_floating_point_v<Type>) {
            return std::make_unique<JsonFloat>(static_cast<double>(value));
        } else if constexpr (std::is_same_v<Type, std::string>) {
            return std::make_unique<JsonString>(std::forward<T>(value));
        } else if constexpr (std::is_same_v<Type, const char*> || std::is_same_v<Type, char*> || std::is_array_v<Type>) {
            return std::make_unique<JsonString>(std::string(value));
        } else {
            static_assert(std::is_same_v<Type, void>, "Type non supporté pour json::make()");
        }
    };

    inline auto null() { return std::make_unique<JsonNull>(); };

    inline auto array() { return std::make_unique<JsonArray>(); };

    inline auto object() { return std::make_unique<JsonObject>(); };
}

#endif //JSONPARSER_JSONFACTORY_HPP