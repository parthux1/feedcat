//
// Created by parthu on 10/18/23.
//
#pragma once

#include <string>
#include <optional>

// must be very basic, Properties define how to store and load themselves
class DatabaseInterface
{
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