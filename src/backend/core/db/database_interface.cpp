//
// Created by parthu on 12/19/23.
//

#include "database_interface.hpp"

void sanitize(std::string& str)
{
    str.erase(std::remove(str.begin(), str.end(), '\''), str.end());
    str.erase(std::remove(str.begin(), str.end(), ';'), str.end());

}

void sanitize(SerializedMapping& mapping)
{
for(const auto& [key, value] : mapping)
    {
        auto key_new = key;
        sanitize(key_new);

        if(key_new != key)
        {
            mapping.erase(key);
            mapping[key_new] = value;
        }
    }
}

void sanitize(SerializedValues& vals)
{
    for(auto& [key, value] : vals)
    {
        auto key_new = key;
        sanitize(key_new);

        if(key_new != key)
        {
            vals.erase(key);
            vals[key_new] = value;
        }
    }
}