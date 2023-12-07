//
// Created by parthu on 12/7/23.
//

#include <property_save_templates.hpp>
#include "FulltextProperty.hpp"

template<>
bool store_property(const FulltextProperty* property, DatabaseInterface* db)
{
    return false;
}

template<>
std::optional<FulltextProperty> load_property(DatabaseInterface* db)
{
    return std::nullopt;
}

static_assert(PropertyDbStrategy<FulltextProperty>);