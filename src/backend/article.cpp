//
// Created by parthu on 8/29/23.
//

#include "article.hpp"

using namespace RSS;


bool Article::operator==(const Article& other) const
{
    return url == other.url
            && title == other.title
            && description == other.description
            && date == other.date
            && rss_source == other.rss_source;
}

std::string Article::to_string() const
{
    return "Title: " + title + "\nDate: " + date + "\nURL: " + url + "\nRSS-Source:" + rss_source + "\nDescription:\n" + description;
}