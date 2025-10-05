#include <iostream>
#include <fstream>
#include <sstream>
#include "json.hpp"

std::string readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void printJson(const JsonValue* value, int indent = 0) {
    if (!value) return;

    const std::string spaces(indent, ' ');

    switch (value->getType()) {
        case JsonType::Object: {
            auto* obj = dynamic_cast<const JsonObject*>(value);
            std::cout << "{\n";
            bool first = true;
            for (const auto& [key, val] : obj->getMembers()) {
                if (!first) std::cout << ",\n";
                first = false;
                std::cout << spaces << "  \"" << key << "\": ";
                printJson(val.get(), indent + 2);
            }
            std::cout << "\n" << spaces << "}";
            break;
        }
        case JsonType::Array: {
            auto* arr = dynamic_cast<const JsonArray*>(value);
            std::cout << "[\n";
            bool first = true;
            for (const auto& elem : arr->getElements()) {
                if (!first) std::cout << ",\n";
                first = false;
                std::cout << spaces << "  ";
                printJson(elem.get(), indent + 2);
            }
            std::cout << "\n" << spaces << "]";
            break;
        }
        case JsonType::String: {
            auto* str = dynamic_cast<const JsonString*>(value);
            std::cout << "\"" << str->getValue() << "\"";
            break;
        }
        case JsonType::Int: {
            auto* num = dynamic_cast<const JsonInteger*>(value);
            std::cout << num->getValue();
            break;
        }
        case JsonType::Float: {
            auto* num = dynamic_cast<const JsonFloat*>(value);
            std::cout << num->getValue();
            break;
        }
        case JsonType::Boolean: {
            auto* b = dynamic_cast<const JsonBoolean*>(value);
            std::cout << (b->getValue() ? "true" : "false");
            break;
        }
        case JsonType::Null:
            std::cout << "null";
            break;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json_file>\n";
        return 1;
    }

    try {
        const std::string &content = readFile(argv[1]);
        std::cout << "=== Contenu brut du fichier ===\n";
        std::cout << content << "\n\n";

        JsonTokenizer tokenizer(content);
        auto tokens = tokenizer.tokenize();

        JsonParser parser(std::move(tokens));
        const auto result = parser.parse();

        std::cout << "=== JSON parsé et affiché ===\n";
        printJson(result.get());
        std::cout << "\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Erreur: " << e.what() << "\n";
        return 1;
    }
}