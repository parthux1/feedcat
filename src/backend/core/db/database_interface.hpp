/*
 * This file contains functions needed for database-property interaction
 *
 * Why not use an actual Strategy Pattern:
 * + static storage would allow registering consistent names for all properties.
 * - no static typeCheck for implemented Strategy bc. it accepts ArticlePropertyInterface*
 *   Could be done via visitor, but this would require a variant including all Property-Implementations
 *   A visitor can also be implemented via these free template functions
 */
#pragma once

#include <string>
#include <optional>
#include <concepts>
#include <ArticlePropertyInterface.hpp>

// free template functions
class DatabaseInterface;

/*!
 *
 * \tparam T ArticleProperty Type to store
 * \param property ArticleProperty Instance to store
 * \param db Db Instance to work on
 * \return an unique id of the stored object if successful
 */
template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
std::optional<std::size_t> store_property(const T* property, DatabaseInterface* db) = delete;

/*!
 *
 * \tparam T ArticleProperty Type to load
 * \param db Db Instance to work on
 * \param id unique id of an object to load
 * \returns an initialized ArticleProperty if existing
 */
template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
std::optional<T> load_property(DatabaseInterface* db, std::size_t id) = delete;

/*!
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 */
template<typename T>
concept PropertyDbStrategy = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>; // Redundant
    requires std::invocable<decltype(load_property<T>), DatabaseInterface*>;
    requires std::invocable<decltype(store_property<T>), T*, DatabaseInterface*>;
};


// Simple Database-oriented wrapper around free template functions
class DatabaseInterface
{
    /*!
     * \brief Calls free function store_property<T>
     */
    template<PropertyDbStrategy T>
    std::optional<std::size_t> store_property(const T* property)
    {
        return store_property(property, this);
    }

    /*!
     * \brief Calls free function load_property<T>
     */
    template<PropertyDbStrategy T>
    std::optional<T> load_property(std::size_t id)
    {
        return load_property<T>(this);
    }
};