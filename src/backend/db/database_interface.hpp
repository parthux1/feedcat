//
// Created by parthu on 10/18/23.
//
#pragma once

#include<backend/article.hpp>

class DatabaseInterface
{
public:
    virtual bool store_article(const RSS::Article& article) = 0;

    /*!
     * Checks if an article exists in the database via comparing the url
     * @param article
     * @return
     */
    virtual bool article_exists(const RSS::Article& article) = 0;
};
