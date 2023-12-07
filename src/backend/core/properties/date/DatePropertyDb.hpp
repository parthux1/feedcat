//
// Created by parthu on 12/7/23.
//

#include <property_save_templates.hpp>
#include "DateProperty.hpp"

template<>
bool store_property(const DateProperty* property, DatabaseInterface* db)
{
    return false;
}

template<>
std::optional<DateProperty> load_property(DatabaseInterface* db)
{
    return std::nullopt;
}

static_assert(PropertyDbStrategy<DateProperty>);