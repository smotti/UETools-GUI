#include "Config.h"






Config::Config(const std::filesystem::path& filePath)
    : FileManager(filePath)
{
}




template <typename T>
struct IsSupportedConfigType
{
    static constexpr bool Value = std::is_same_v<T, bool>
                                  || std::is_same_v<T, int>
                                  || std::is_same_v<T, float>
                                  || std::is_same_v<T, SDK::FVector>
                                  || std::is_same_v<T, std::string>;
};

static std::string ToLowerCopy(std::string s)
{
    for (char& c : s)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

    return s;
}

static std::string FloatToString(const float value)
{
    std::ostringstream stringStream;
    stringStream << std::setprecision(9) << value;
    return stringStream.str();
}




bool Config::Load()
{
    _values.clear();

    std::vector<std::string> lines;
    if (LoadLines(&lines) == false)
        return false;

    for (const std::string& rawLine : lines)
    {
        const std::string line = Trim(rawLine);
        if (IsLineCommentOrEmpty(line) == true)
            continue;

        const std::optional<std::pair<std::string, std::string>> KeyValue = SplitKeyValue(line);
        if (KeyValue.has_value() == false)
            continue;

        const std::string key = Trim(KeyValue->first);
        if (key.empty() == true)
            continue;

        const std::string rawValue = Trim(KeyValue->second);
        const std::optional<Value> value = ParseValueWithOptionalType(rawValue);
        if (value.has_value() == false)
            continue;

        _values[key] = *value;
    }

    return true;
}

bool Config::Save()
{
    std::vector<std::string> lines;
    lines.reserve(_values.size());

    for (const auto& value : _values)
        lines.push_back(ValueToLine(value.first, value.second));

    return SaveLines(lines);
}




template <typename T>
std::optional<T> Config::Get(const std::string& key)
{
    static_assert(IsSupportedConfigType<T>::Value == true, "Unsupported config type.");

    const auto value = _values.find(key);
    if (value == _values.end())
        return std::nullopt;

    if (std::holds_alternative<T>(value->second) == true)
        return std::get<T>(value->second);

    if (std::holds_alternative<std::string>(value->second) == true)
    {
        const std::string& text = std::get<std::string>(value->second);

        if constexpr (std::is_same_v<T, bool>)
            return TryParseBool(text);

        if constexpr (std::is_same_v<T, int>)
            return TryParseInt(text);

        if constexpr (std::is_same_v<T, float>)
            return TryParseFloat(text);

        if constexpr (std::is_same_v<T, SDK::FVector>)
            return TryParseFVector(text);

        if constexpr (std::is_same_v<T, std::string>)
            return text;
    }

    return std::nullopt;
}

template <typename T>
void Config::Set(const std::string& key, const T& value)
{
    static_assert(IsSupportedConfigType<T>::Value == true, "Unsupported config type.");

    if (key.empty() == true)
        return;

    _values[key] = value;
}
void Config::Set(const std::string& key, const char* value)
{
    if (key.empty() == true || value == nullptr)
        return;

    _values[key] = std::string(value);
}
void Config::Set(const std::string& key, const SDK::FVector& value)
{
    if (key.empty() == true)
        return;

    _values[key] = value;
}




bool Config::HasKey(const std::string& key)
{
    return _values.find(key) != _values.end();
}

void Config::Remove(const std::string& key)
{
    _values.erase(key);
}

void Config::Clear()
{
    _values.clear();
}




std::string Config::Trim(const std::string& text)
{
    size_t start = 0;
    size_t end = text.size();

    while (start < end && std::isspace(static_cast<unsigned char>(text[start])) != 0)
        ++start;

    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0)
        --end;

    return text.substr(start, end - start);
}

bool Config::IsLineCommentOrEmpty(const std::string& line)
{
    if (line.empty() == true)
        return true;

    if (line.rfind("#", 0) == 0)
        return true;

    if (line.rfind(";", 0) == 0)
        return true;

    if (line.rfind("//", 0) == 0)
        return true;

    return false;
}




bool Config::ConsumeFloat(const std::string& text, size_t& inOutPos, float& outValue)
{
    while (inOutPos < text.size() && (text[inOutPos] == ' ' || text[inOutPos] == '\t' || text[inOutPos] == ','))
        ++inOutPos;

    if (inOutPos >= text.size())
        return false;

    const char* begin = text.data() + inOutPos;
    const char* end = text.data() + text.size();

    std::from_chars_result fromCharsResult = std::from_chars(begin, end, outValue, std::chars_format::general);
    if (fromCharsResult.ec != std::errc())
        return false;

    inOutPos = static_cast<size_t>(fromCharsResult.ptr - text.data());
    return true;
}




std::optional<std::pair<std::string, std::string>> Config::SplitKeyValue(const std::string& line)
{
    const size_t pos = line.find('=');
    if (pos == std::string::npos)
        return std::nullopt;

    const std::string left = line.substr(0, pos);
    const std::string right = line.substr(pos + 1);

    return std::make_pair(left, right);
}

std::optional<Config::Value> Config::ParseValueWithOptionalType(const std::string& rawValue)
{
    const size_t colonPos = rawValue.find(':');

    if (colonPos == std::string::npos)
        return Value(rawValue);

    const std::string typePart = ToLowerCopy(Trim(rawValue.substr(0, colonPos)));
    const std::string valuePart = Trim(rawValue.substr(colonPos + 1));

    if (typePart == "bool")
    {
        const std::optional<bool> v = TryParseBool(valuePart);
        if (v.has_value() == false)
            return std::nullopt;

        return Value(*v);
    }

    if (typePart == "int")
    {
        const std::optional<int> v = TryParseInt(valuePart);
        if (v.has_value() == false)
            return std::nullopt;

        return Value(*v);
    }

    if (typePart == "float")
    {
        const std::optional<float> v = TryParseFloat(valuePart);
        if (v.has_value() == false)
            return std::nullopt;

        return Value(*v);
    }

    if (typePart == "fvector")
    {
        const std::optional<SDK::FVector> v = TryParseFVector(valuePart);
        if (v.has_value() == false)
            return std::nullopt;

        return Value(*v);
    }

    if (typePart == "string")
        return Value(valuePart);

    // Unknown type token -> treat everything as string.
    return Value(rawValue);
}




std::string Config::ValueToLine(const std::string& key, const Value& value)
{
    if (std::holds_alternative<bool>(value) == true)
        return key + " = bool:" + (std::get<bool>(value) ? "true" : "false");

    if (std::holds_alternative<int>(value) == true)
        return key + " = int:" + std::to_string(std::get<int>(value));

    if (std::holds_alternative<float>(value) == true)
        return key + " = float:" + FloatToString(std::get<float>(value));

    if (std::holds_alternative<SDK::FVector>(value) == true)
    {
        const SDK::FVector& v = std::get<SDK::FVector>(value);

        std::ostringstream ss;
        ss << key << " = fvector:"
            << std::setprecision(9) << v.X << " "
            << std::setprecision(9) << v.Y << " "
            << std::setprecision(9) << v.Z;

        return ss.str();
    }

    return key + " = string:" + std::get<std::string>(value);
}




std::optional<bool> Config::TryParseBool(const std::string& text)
{
    const std::string v = ToLowerCopy(Trim(text));

    if (v == "true" || v == "1")
        return true;

    if (v == "false" || v == "0")
        return false;

    return std::nullopt;
}

std::optional<int> Config::TryParseInt(const std::string& text)
{
    const std::string t = Trim(text);
    if (t.empty() == true)
        return std::nullopt;

    int value = 0;

    const char* begin = t.data();
    const char* end = t.data() + t.size();

    std::from_chars_result r = std::from_chars(begin, end, value);
    if (r.ec != std::errc() || r.ptr != end)
        return std::nullopt;

    return value;
}

std::optional<float> Config::TryParseFloat(const std::string& text)
{
    const std::string t = Trim(text);
    if (t.empty() == true)
        return std::nullopt;

    float value = 0.0f;

    const char* begin = t.data();
    const char* end = t.data() + t.size();

    std::from_chars_result r = std::from_chars(begin, end, value, std::chars_format::general);
    if (r.ec != std::errc() || r.ptr != end)
        return std::nullopt;

    return value;
}

std::optional<SDK::FVector> Config::TryParseFVector(const std::string& text)
{
    const std::string t = Trim(text);
    if (t.empty() == true)
        return std::nullopt;

    size_t pos = 0;

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (ConsumeFloat(t, pos, x) == false)
        return std::nullopt;

    if (ConsumeFloat(t, pos, y) == false)
        return std::nullopt;

    if (ConsumeFloat(t, pos, z) == false)
        return std::nullopt;

    SDK::FVector fVector;
    fVector.X = x;
    fVector.Y = y;
    fVector.Z = z;

    return fVector;
}




// Explicit instantiations to keep all template logic in .cpp
template std::optional<bool> Config::Get<bool>(const std::string& key);
template std::optional<int> Config::Get<int>(const std::string& key);
template std::optional<float> Config::Get<float>(const std::string& key);
template std::optional<SDK::FVector> Config::Get<SDK::FVector>(const std::string& key);
template std::optional<std::string> Config::Get<std::string>(const std::string& key);

template void Config::Set<bool>(const std::string& key, const bool& value);
template void Config::Set<int>(const std::string& key, const int& value);
template void Config::Set<float>(const std::string& key, const float& value);
template void Config::Set<SDK::FVector>(const std::string& key, const SDK::FVector& value);
template void Config::Set<std::string>(const std::string& key, const std::string& value);

