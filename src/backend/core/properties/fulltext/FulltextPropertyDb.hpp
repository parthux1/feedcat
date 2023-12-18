//
// Created by parthu on 12/7/23.
//

#include <db/database_interface.hpp>
#include "FulltextProperty.hpp"

template<>
std::optional<DatabaseID> store_property(const FulltextProperty* property, DatabaseInterface* db)
{
    return std::nullopt;
}

template<>
std::optional<FulltextProperty> load_property(DatabaseInterface* db, const DatabaseID& id)
{
    return std::nullopt;
}