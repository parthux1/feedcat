//
// Created by parthu on 12/28/23.
//
#include <string>
#include <algorithm>
#include <functional>

std::string sanitize(std::string str);

class SanitizedString {
public:
    SanitizedString(std::string str)
    {
        str = sanitize(str);
    }

    bool operator==(const SanitizedString& other) const noexcept;

    const std::string& get() const noexcept;

private:
    std::string str_;
};

/*
 * Implement std::hash functionality, so we can use SanitizedString as a key in std::unordered_map
 */
template <>
struct std::hash<SanitizedString>
{
    std::size_t operator()(const SanitizedString& k) const
    {
        return std::hash<std::string>{}(k.get());
    }
};