//
// Created by parthu on 10/18/23.
//
#pragma once

#include<backend/article.hpp>

class DatabaseInterface
{
public:
    /*
     * Stores an article in the database
     * @param article
     * @return true if successful
     */
    virtual bool store_article(const RSS::Article& article) = 0;

    /*!
     * Checks if an article exists in the database via comparing the url
     * @param article
     * @return true if an entry with the given URL exists
     * @throws if article_exists(std::string) throws
     */
    virtual bool article_exists(const RSS::Article& article) const = 0;

    virtual bool article_exists(const std::string& url) const = 0;

    /*!
     * Get an article by URL
     * @param url URL to get
     * @return RSS:Article if the url exists in the database
     */
    virtual std::optional<RSS::Article> get_article(std::string url) const = 0;

    virtual std::size_t count_articles() const = 0;
};
