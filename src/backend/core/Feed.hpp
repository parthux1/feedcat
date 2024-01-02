//
// Created by parthu on 11/18/23.
//
#pragma once

#include <string>
#include <chrono>
#include <list>

#include <core/Article.hpp>
#include <core/network/FullTextParserStrategy.hpp>
#include <core/network/parser_rss.hpp>

class Feed
{
public:
    /*!
     * \param url URL of a single RSS feed
     */
    Feed(const std::string& url);

    Feed(const Feed& other);

    /*!
     * \brief Download the RSS feed and handle articles published since last_update
     * \param strategy Optional strategy to use for fulltext parsing
     */
    void update(const std::optional<std::shared_ptr<FullTextParserStrategy>>& strategy = std::nullopt);

// Members
public:
    std::string url;
    std::time_t last_update = -1; // invalid point in time

    std::list<Article> articles = {};
};
