#include "JsonTokenizer.hpp"
#include <iostream>

int main() {
    // Test 1 : JSON simple
    std::string json1 = R"({
        "name": "Alice",
        "age": 30,
        "score": 95.5,
        "active": true,
        "balance": -12.34,
        "items": [1, 2, 3],
        "address": null
    })";

    std::cout << "=== Test 1 : JSON complet ===" << std::endl;
    Tokenizer tokenizer1(json1);
    auto tokens1 = tokenizer1.tokenize();

    for (const auto& token : tokens1) {
        std::cout << "Token: " << tokenTypeToString(token.type);
        if (!token.value.empty()) {
            std::cout << " | Value: '" << token.value << "'";
        }
        std::cout << " | Line: " << token.line
                  << " | Column: " << token.column << std::endl;
    }

    // Test 2 : String avec échappements
    std::cout << "\n=== Test 2 : Échappements ===" << std::endl;
    std::string json2 = R"({"message": "Hello\nWorld\t\"Quote\""})";

    Tokenizer tokenizer2(json2);
    auto tokens2 = tokenizer2.tokenize();

    for (const auto& token : tokens2) {
        std::cout << "Token: " << tokenTypeToString(token.type);
        if (!token.value.empty()) {
            std::cout << " | Value: '" << token.value << "'";
        }
        std::cout << std::endl;
    }

    // Test 3 : Nombres
    std::cout << "\n=== Test 3 : Nombres ===" << std::endl;
    std::string json3 = R"([123, -456, 78.9, -0.123])";

    Tokenizer tokenizer3(json3);
    auto tokens3 = tokenizer3.tokenize();

    for (const auto& token : tokens3) {
        std::cout << "Token: " << tokenTypeToString(token.type);
        if (!token.value.empty()) {
            std::cout << " | Value: '" << token.value << "'";
        }
        std::cout << std::endl;
    }

    // Test 4 : Booléens et null
    std::cout << "\n=== Test 4 : Booléens et null ===" << std::endl;
    std::string json4 = R"({"a": true, "b": false, "c": null})";

    Tokenizer tokenizer4(json4);
    auto tokens4 = tokenizer4.tokenize();

    for (const auto& token : tokens4) {
        std::cout << "Token: " << tokenTypeToString(token.type);
        if (!token.value.empty()) {
            std::cout << " | Value: '" << token.value << "'";
        }
        std::cout << std::endl;
    }

    // Test 5 : JSON invalide (pour tester les erreurs)
    std::cout << "\n=== Test 5 : Erreurs ===" << std::endl;
    std::string json5 = R"({"unclosed": "string)";

    Tokenizer tokenizer5(json5);
    auto tokens5 = tokenizer5.tokenize();

    for (const auto& token : tokens5) {
        std::cout << "Token: " << tokenTypeToString(token.type);
        if (!token.value.empty()) {
            std::cout << " | Value: '" << token.value << "'";
        }
        if (token.type == TokenType::ERROR) {
            std::cout << " ⚠️ ERROR at line " << token.line
                      << ", column " << token.column;
        }
        std::cout << std::endl;
    }
    
    return 0;
}