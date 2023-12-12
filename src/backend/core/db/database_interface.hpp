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

template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
bool store_property(const T* property, DatabaseInterface* db) = delete;

// TODO: additional information for loading required
template<typename T>
requires std::derived_from<T, ArticlePropertyInterface>
std::optional<T> load_property(DatabaseInterface* db) = delete;

template<typename T>
/*!
 * \brief Use this concept to check if all needed functions for loose PropertyDbStrategy are implemented
 * \note Apply this concept after overloading functions. Otherwise the call to decltype() will default to base templates
 * \example static_assert(PropertyDbStrategy<MyPropertyType>);
 * \example See src/backend/properties/ArticleBasePropertyDb.hpp
 */
concept PropertyDbStrategy = requires()
{
    requires std::derived_from<T, ArticlePropertyInterface>; // Redundant
    requires std::invocable<decltype(load_property<T>), DatabaseInterface*>;
    requires std::invocable<decltype(store_property<T>), T*, DatabaseInterface*>;
};


// Simple Database-oriented wrapper around free template functions
class DatabaseInterface
{
    template<PropertyDbStrategy T>
    bool store_property(const T* property)
    {
        store_property(property, this);
    }

    template<PropertyDbStrategy T>
    std::optional<T> load_property()
    {
        return load_property<T>(this);
    }
};


// old DB-Interface directly working on articles
#if false
class DatabaseInterface
{
    // NVI functions
    // When implementing a single overload all base-class overloads are shadowed.
    // By providing a function-overload similar to the _impl we still allow "normal" access to it.
public:
    /*!
     * Overrides an existing article with the given URL with this content
     * @param article_new new content to store.
     * @returns amount of updated entries.
     */
    std::size_t update_article(const Article& article_new);

    /*!
     * Overrides an existing article with this content. URL will be updated to!
     * @param url_old url-key to overwrite
     * @param article_new new content to store.
     * @returns amount of updated entries.
     */
    std::size_t update_article(const std::string& url_old, const Article& article_new);

    /*!
     * Checks if an article exists in the database via comparing the url.
     * @param article
     * @return true if an entry with the given URL exists.
     * @throws if article_exists(std::string) throws.
     */
    bool article_exists(const Article& article) const;

    /*!
     * Checks if an article exists in the database via comparing the url.
     * @param url
     * @return true if an entry with the given URL exists.
     * @throws if database access fails.
     */
    bool article_exists(const std::string& url) const;

    // NVI implementations
protected:
    /*!
     * Overrides an existing article with this content. URL will be updated to!
     * @param url_old url-key to overwrite
     * @param article_new new content to store.
     * @returns amount of updated entries.
     */
    virtual std::size_t update_article_impl(const std::string& url_old, const Article& article_new) = 0;

    /*!
     * Checks if an article exists in the database via comparing the url.
     * @param url
     * @return true if an entry with the given URL exists.
     * @throws if database access fails.
     */
    virtual bool article_exists_impl(const std::string& url) const = 0;

    // other function overrides
public:
    /*!
     * Stores an article in the database
     * @param article
     * @return true if successful
     */
    virtual bool store_article(const Article& article) = 0;

    /*!
     * Get an article by URL
     * @param url URL to get
     * @return RSS:Article if the url exists in the database.
     */
    virtual std::optional<Article> get_article(std::string url) const = 0;

    /*!
     * @returns amount of entities in the database.
     */
    virtual std::size_t count_articles() const = 0;
};

#endif