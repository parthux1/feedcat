//
// Created by parthu on 12/7/23.
//

#include <db/database_interface.hpp>
#include "DateProperty.hpp"

template<>
std::optional<DatabaseID> store_property(const DateProperty* property, DatabaseInterface* db)
{
    return std::nullopt;
}

template<>
std::optional<DateProperty> load_property(DatabaseInterface* db, const DatabaseID& id)
{
    return std::nullopt;
}