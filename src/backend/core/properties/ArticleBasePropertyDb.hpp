//
// Created by parthu on 11/21/23.
//
#pragma once

#include <core/properties/ArticleBaseProperty.hpp>
#include <core/db/property_serialize_functions.hpp>

template<>
std::string table_name<ArticleBaseProperty>();

template<>
SerializedMapping serialize_mapping<ArticleBaseProperty>();

template<>
SerializedValues serialize(const ArticleBaseProperty& obj);

template<>
std::optional<ArticleBaseProperty> deserialize(const SerializedValues& obj);
