#include <iostream>
#include <string>
#include "JsonFactory.hpp"
int main()
{
    auto nullValue = json::null();
    auto boolValue = json::make(true);
    auto intValue = json::make(42);
    auto int64Value = json::make(42L);
    auto floatValue = json::make(3.14f);
    auto doubleValue = json::make(3.14159);
    auto stringValue = json::make("Hello JSON");
    auto stringValue2 = json::make(std::string("C++ string"));

    std::cout << "Création avec template factory (déduction auto):\n";
    nullValue->print();
    boolValue->print();
    intValue->print();
    int64Value->print();
    floatValue->print();
    doubleValue->print();
    stringValue->print();
    stringValue2->print();

    std::cout << "\nTest avec différents types entiers:\n";
    auto shortVal = json::make(short(10));
    auto intVal = json::make(20);
    auto longVal = json::make(30L);
    auto longlongVal = json::make(40LL);

    std::cout << "short: " << shortVal->toString() << "\n";
    std::cout << "int: " << intVal->toString() << "\n";
    std::cout << "long: " << longVal->toString() << "\n";
    std::cout << "long long: " << longlongVal->toString() << "\n";

    std::cout << "\nTest polymorphisme:\n";
    std::vector<std::unique_ptr<JsonValue>> values;
    values.push_back(json::null());
    values.push_back(json::make(false));
    values.push_back(json::make(100));
    values.push_back(json::make(2.71828));
    values.push_back(json::make("Template magic!"));

    for (const auto& v : values) {
        std::cout << "  " << v->toString() << "\n";
    }
}
