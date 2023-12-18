//
// Created by parthu on 11/21/23.
//
#pragma once

#include <properties/ArticleBaseProperty.hpp>
#include <db/database_interface.hpp>

template<>
std::optional<DatabaseID> store_property(const ArticleBaseProperty* property, DatabaseInterface* db)
{
    return std::nullopt;
}

template<>
std::optional<ArticleBaseProperty> load_property(DatabaseInterface* db, const DatabaseID& id)
{
    return std::nullopt;
}