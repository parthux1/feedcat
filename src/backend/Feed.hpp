//
// Created by parthu on 11/18/23.
//
#pragma once

#include <string>
#include <chrono>
#include <list>

#include <Article.hpp>

class Feed
{
public:
    /*!
     * \param url URL of a single RSS feed
     */
    Feed(const std::string& url);

// Members
public:
    std::string url;
    std::time_t last_update = -1; // invalid point in time

    std::list<Article> articles = {};
};
