#include <iostream>
#include "Json.h"

int main()
{
    Json::Object obj = {
        {"name", "John Doe"},
        {"age", 30},
        {"is_student", false},
        {"address", Json::Object{
            {"street", "123 Main St"},
            {"city", "Somewhere"},
            {"zipcode", "12345"}
        }},
    };
    obj.emplace("married", false);
    obj.emplace("children", Json::Array{});

    Json::Serialize(obj, "test.json");
    return 0;
}
