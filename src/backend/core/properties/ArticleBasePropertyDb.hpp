//
// Created by parthu on 11/21/23.
//
#pragma once

#include <properties/ArticleBaseProperty.hpp>
#include <db/property_serialize_functions.hpp>

template<>
std::string table_name<ArticleBaseProperty>()
{
    return "article_base";
}

template<>
SerializedMapping serialize_mapping<ArticleBaseProperty>()
{
    return {
        {"url", DatabaseFieldType::TEXT},
        {"description", DatabaseFieldType::TEXT},
        {"rss_url", DatabaseFieldType::TEXT},
        {"title", DatabaseFieldType::TEXT},
    };
}

template<>
SerializedValues serialize(const ArticleBaseProperty& obj)
{
    return {
        {"url", obj.url},
        {"description", obj.description},
        {"rss_url", obj.rss_url},
        {"title", obj.title},
    };
}

template<>
std::optional<ArticleBaseProperty> deserialize(const SerializedValues& obj)
{
    if (obj.contains("url") && obj.contains("description") && obj.contains("rss_url") && obj.contains("title"))
    {
        try
        {
            return ArticleBaseProperty{
                    std::get<std::string>(obj.at("title")),
                    std::get<std::string>(obj.at("url")),
                    std::get<std::string>(obj.at("description")),
                    std::get<std::string>(obj.at("rss_url")),
            };
        }catch (std::bad_variant_access& e)
        {
            SPDLOG_ERROR("Could not deserialize ArticleBaseProperty: {}", e.what());
        }
    }
    return std::nullopt;
}