//
// Created by parthu on 12/19/23.
//

#include "database_interface.hpp"

SanitizedMapping sanitize(SerializedMapping& mapping)
{
    SanitizedMapping res{};
    for(const auto& [key, value] : mapping)
        {
            SanitizedString key_new{key};
            res.insert({key_new, value});
        }

    return res;
}

SanitizedValues sanitize(SerializedValues& vals)
{
    SanitizedValues res;
    for(auto& [key, value] : vals)
    {
        SanitizedString key_new{key};
        if(key_new != key)
        {
            res.insert({key_new, value});
        }
    }

    return res;
}