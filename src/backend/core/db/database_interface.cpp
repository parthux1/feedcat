//
// Created by parthu on 12/19/23.
//

#include "database_interface.hpp"

SanitizedMapping sanitize(const SerializedMapping& mapping)
{
    SanitizedMapping res{};
    for(const auto& [key, value] : mapping)
        {
            SanitizedString key_new{key};
            res.insert({key_new, value});
        }

    return res;
}

SanitizedValues sanitize(const SerializedValues& vals)
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

std::optional<DatabaseID> DatabaseInterface::store_article(const Article &article)
{
    SPDLOG_CRITICAL("Not implemented");
    return std::nullopt;
    for(const auto&[key, property] : article.properties)
    {
    }
}

void DatabaseInterface::append_ids(SerializedMapping &mapping)
{
    mapping["id"] = DatabaseFieldType::PRIMARY_KEY;
    mapping["article_ref"] = DatabaseFieldType::FOREIGN_KEY; // TODO: don't do this for the base property
}