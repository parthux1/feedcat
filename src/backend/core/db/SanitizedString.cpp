//
// Created by parthu on 12/28/23.
//

#include "SanitizedString.hpp"

std::string sanitize(std::string str)
{
    str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
    str.erase(std::remove(str.begin(), str.end(), ';'), str.end());

    return str;
}

SanitizedString::SanitizedString(std::string str)
{
    str = sanitize(str);
}

bool SanitizedString::operator==(const SanitizedString& other) const noexcept
{
    return str_ == other.str_;
}


const std::string& SanitizedString::data() const noexcept
{
    return str_;
}