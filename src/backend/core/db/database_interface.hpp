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
#include <list>
#include <concepts>

#include <ArticlePropertyInterface.hpp>

using DatabaseID = std::size_t;

class DatabaseInterface; // forward declaration needed for free template functions

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
std::optional<T> load_property(DatabaseInterface* db, const DatabaseID& id) = delete;

/*!
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 */
template<typename T>
concept PropertyDbStrategy = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>; // Redundant
    requires std::invocable<decltype(load_property<T>), DatabaseInterface*, DatabaseID>;
    requires std::invocable<decltype(store_property<T>), T*, DatabaseInterface*>;
};


/*!
 * \brief Interface for simpler database interactions with custom connectors
 */
class DatabaseInterface
{
public:
    /*!
     * \brief Calls free function store_property<T>
     */
    template<PropertyDbStrategy T>
    std::optional<DatabaseID> store_property(const T* property)
    {
        return store_property(property, this);
    }

    /*!
     * \brief Calls free function load_property<T>
     */
    template<PropertyDbStrategy T>
    std::optional<T> load_property(const DatabaseID& id)
    {
        return load_property<T>(this);
    }

    /*!
     * \brief Checks if a property with the given id exists
     */
    virtual bool has_id(const DatabaseID& id) const = 0;

    /*!
     * \brief Returns the number of stored properties
     */
    virtual std::list<DatabaseID> get_all_ids() const = 0;
};