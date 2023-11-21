//
// Created by parthu on 11/21/23.
//
#pragma once
#include <concepts>
#include <optional>
#include <db/database_interface.hpp>
#include <ArticlePropertyHash.hpp>
#include <ArticlePropertyInterface.hpp>

/*
 * This file contains functions needed for database-property interaction
 *
 * Why not use an actual Strategy Pattern:
 * + static storage would allow registering consistent names for all properties.
 * - no static typeCheck for implemented Strategy bc. it accepts ArticlePropertyInterface*
 *   Could be done via visitor, but this would require a variant including all Property-Implementations
 *   A visitor can also be implemented via these free template functions
 */

template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
bool store_property(const T* property, DatabaseInterface* db) = delete;

template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
std::optional<T> load_property(DatabaseInterface* db) = delete;


template<typename T>
/*!
 * \brief Use this concept to check if all needed functions for loose PropertyDbStrategy are implemented
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 * \example static_assert(PropertyDbStrategy<MyPropertyType>);
 * \example See src/backend/properties/ArticleBasePropertyDb.hpp
 * @tparam T
 */
concept PropertyDbStrategy = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>; // Redundant
    requires std::invocable<decltype(load_property<T>), DatabaseInterface*>;
    requires std::invocable<decltype(store_property<T>), T*, DatabaseInterface*>;
};
