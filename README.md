# JSON Parser

A lightweight C++ JSON parser for reading JSON files easily.

## Features

- Simple and easy-to-use interface
- Parses JSON objects and arrays
- Supports strings, numbers, booleans, and null values

## Installation

Clone the repository and include `Json.h` and `Json.cpp` in your project.

```sh
# Clone the repository
git clone https://github.com/MarkusBackman233/JFast
```

Include the header in your project:

```cpp
#include "Json.h"
```

## Usage

### Parsing a JSON file

```cpp
#include "Json.h"

int main()
{
    Json j = Json::ParseFile("test.json");
    
    std::string name = j["Name"].AsString();
    float age = j["Age"].AsInt();
    return 0;
}
```

### Writing a JSON file

```cpp
#include "Json.h"

int main()
{
    Json::Object j = {
        {"name", "John Doe"},
        {"age", 30},
        {"address", Json::Object{
            {"street", "123 Main St"},
            {"city", "Somewhere"},
        }},
    };
    // or
    j.emplace("married", false);
    j.emplace("children", Json::Array{});

    Json::Serialize(j, "test.json");
}
```

### Supported Data Types

- **Strings**: `AsString()`
- **Float**: `AsFloat()`
- **Int**: `AsInt()`
- **Booleans**: `AsBool()`
- **Objects**: `AsObject()`
- **Arrays**: `AsArray()`

### Example JSON File

```json
{
    "Name": "John Doe",
    "Age": 30,
    "Married": false,
    "Children": ["Alice", "Bob"]
}
```


### Iterating Over JSON Arrays
Since arrays are stored as `std::vector<Json>`, they can be iterated easily:

```cpp
for (const Json& item : j["Children"].AsArray())
{
    std::string childName = item.AsString();
}
```

## License

This project is licensed under the MIT License.

