//
// Created by parthu on 10/20/23.
//
#include "database_interface.hpp"

std::size_t DatabaseInterface::update_article(const RSS::Article& article_new)
{
    return update_article_impl(article_new.url, article_new);
}

std::size_t DatabaseInterface::update_article(const std::string& url_old, const RSS::Article& article_new)
{
    return update_article_impl(url_old, article_new);
}

bool DatabaseInterface::article_exists(const RSS::Article& article) const
{
    return article_exists_impl(article.url);
}

bool DatabaseInterface::article_exists(const std::string& url) const
{
    return article_exists_impl(url);
}