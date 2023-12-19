//
// Created by parthu on 12/19/23.
//
#pragma once

#include <db/database_types.hpp>
#include <ArticlePropertyInterface.hpp>

template<typename T>
SerializedMapping serialize_mapping() = delete;

template<typename T>
SerializedValues serialize(const T& obj) = delete;

template<typename T>
std::optional<T> deserialize(const SerializedValues& obj) = delete;

template<typename T>
std::string table_name() = delete;

/*!
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 */
template<typename T>
concept PropertyIsSerializable = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>;
    requires std::invocable<decltype(serialize_mapping<T>)>;
    requires std::invocable<decltype(serialize<T>), T>;
    requires std::invocable<decltype(deserialize<T>), SerializedValues>;
};

template<typename T>
concept PropertyIsStorable = requires()
{
    requires PropertyIsSerializable<T>;
    requires std::invocable<decltype(table_name<T>)>;
};