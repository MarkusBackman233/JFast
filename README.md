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
git clone https://github.com/yourusername/json-parser.git
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
    Json j = Json::Parse("C:\\Users\\Markus\\Desktop\\test.json");
    
    std::string name = j["Name"].AsString();
    float age = j["Age"].AsFloat();
    return 0;
}
```

### Supported Data Types

- **Strings**: `AsString()`
- **Numbers**: `AsFloat()`
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
for (const auto& item : j["Children"].AsArray())
{
    std::string childName = item.AsString();
}
```

## License

This project is licensed under the MIT License.

