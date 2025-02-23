#pragma once
#include <string>
#include <variant>
#include <map>
#include <vector>


class Json
{
public:
	using Object = std::map<std::string, Json>;
	using Array  = std::vector<Json>;

	static Json Parse(const std::string& file);

private:
	static void SkipWhitespace(const std::string& file, size_t& index);
	static Json ParseValue(const std::string& file, size_t& index, bool asArray = false);
	static std::string GetNextKey(const std::string& file, size_t& index);

public:
	Json(const Object& value){ m_value = value; }
	Json(const std::string& value){ m_value = value; }
	Json(bool value){ m_value = value; }
	Json(float value) { m_value = value; };
	Json(const Array& value){ m_value = value; }

	Json operator[](const std::string& key);

	const std::string& AsString();
	Object& AsObject();
	Array& AsArray();
	float AsFloat();
	bool AsBool();

private:
	void AddElement(const Json& json, bool asArray = false);
	std::variant<Object, Array, std::string, float, bool> m_value;
};

