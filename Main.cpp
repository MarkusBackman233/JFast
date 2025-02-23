#include <iostream>

#include "Json.h"

int main()
{
    auto j = Json::Parse("C:\\Users\\Markus\\Desktop\\test.json");

    std::cout << j["Name"].AsString() << std::endl;
    std::cout << j["Age"].AsFloat() << std::endl;
    return 0;
}
