#include "Json.h"
#include <fstream>
#include <iostream>


Json Json::Parse(const std::string& file)
{
    std::ifstream f(file);
    if (!f)
    {
        std::cerr << "Error opening file!" << std::endl;
    }
    std::string data = std::string((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    f.close();

    size_t index = 0;
    Json json = ParseValue(data, index);

    return std::move(json);
}

void Json::SkipWhitespace(const std::string& file, size_t& index)
{
    while (index < file.size() && std::isspace(file[index])) 
    {
        ++index;
    }
}

Json Json::ParseValue(const std::string& file, size_t& index, bool asArray /* = false*/)
{
    Object object;
    Array array;

    auto AddItem = [&](const std::string& key, const Json& json)
    {
        if (asArray)
        {
            array.push_back(json);
        }
        else
        {
            object.try_emplace(key, json);
        }
    };


    while (true)
    {
        std::string key;
        if (asArray)
        {
            SkipWhitespace(file, index);

            std::cout << file[index] << std::endl;
            if (file[index] == ']')
            {
                break;
            }

            index++;
            SkipWhitespace(file, index);
        }
        else
        {
            key = GetNextKey(file, index);
            if (key == "null")
            {
                break;
            }
            SkipWhitespace(file, index);
            index++; // skip the ":"
            SkipWhitespace(file, index);
        }


        switch (file[index])
        {
        case '{':
            AddItem(key, ParseValue(file, index));
            break;
        case '\"':
            AddItem(key, GetNextKey(file, index));
            break;        
        case '[':
            AddItem(key, ParseValue(file, index, true));
            break;
        default:

            if (file.substr(index, 4) == "null") 
            {
                index += 4;
            }
            else if (file.substr(index, 4) == "true")
            {
                AddItem(key, Json(true));
                index += 4;
            }            
            else if (file.substr(index, 5) == "false")
            {
                AddItem(key, Json(false));
                index += 5;
            }
            else
            { // if it is not any of the before its a number
                for (size_t i = index; i < file.size(); i++)
                {
                    char ch = file[i];
                    if (isdigit(ch) == false && ch != '.' && ch != '-')
                    {
                        std::string contents(file.data() + index, i - index );
                        index = i ;
                        AddItem(key, Json(std::stof(contents)));
                        break;
                    }
                }
            }
            break;
        }
    }

    if (asArray)
    {
        return Json(array);
    }

    return Json(object);
}



std::string Json::GetNextKey(const std::string& file, size_t& index)
{
    size_t startIndex = std::string::npos;
    for (size_t i = index; i < file.size(); i++)
    {
        if (file[i] == '}')
        {
            index = i + 1;
            return "null";
        }
        if (file[i] != '\"')
        {
            continue;
        }


        if (startIndex == std::string::npos)
        {
            startIndex = i;
        }
        else
        {
            std::string contents(file.data() + startIndex + 1, i - startIndex - 1);
            index = i + 1;
           
            return contents;
        }
    }
    return "null";
}



Json Json::operator[](const std::string& key)
{
    return AsObject().find(key)->second;
}

const std::string& Json::AsString()
{
    return std::get<std::string>(m_value);
}

Json::Object& Json::AsObject()
{
    return std::get<Json::Object>(m_value);
}

Json::Array& Json::AsArray()
{
    return std::get<Json::Array>(m_value);
}

float Json::AsFloat()
{
    return std::get<float>(m_value);
}

bool Json::AsBool()
{
    return std::get<bool>(m_value);
}

