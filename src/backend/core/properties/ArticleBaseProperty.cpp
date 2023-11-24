//
// Created by parthu on 11/19/23.
//

#include "ArticleBaseProperty.hpp"

#include <utility>

ArticleBaseProperty::ArticleBaseProperty(std::string  title, std::string  url, std::string  rss_url, std::string description)
    : url(std::move(url)),
      rss_url(std::move(rss_url)),
      title(std::move(title)),
      description(std::move(description))
{

}

bool ArticleBaseProperty::operator==(const ArticleBaseProperty& other) const
{
    return url == other.url
            && rss_url == other.rss_url
            && title == other.title
            && date == other.date
            && description == other.description
            && fulltext == other.fulltext;
}

std::string ArticleBaseProperty::to_string() const
{
    std::string ret_val = "Title: " + title + "\nDescription" + description + "\nURL: " + url + "\nRSS-Source:" + rss_url;

    if(date.has_value()) ret_val += "\nPubDate: " + std::to_string(date.value());
    if(fulltext.has_value()) ret_val += "\nFulltext: " + fulltext.value();

    return ret_val;
}

// Builder
ArticleBaseProperty& ArticleBaseProperty::set_url(const std::string& url_new)
{
    url = url_new;
    return *this;
}

ArticleBaseProperty& ArticleBaseProperty::set_rss_url(const std::string& rss_url_new)
{
    rss_url = rss_url_new;
    return *this;
}

ArticleBaseProperty& ArticleBaseProperty::set_title(const std::string& title_new)
{
    title = title_new;
    return *this;
}

ArticleBaseProperty& ArticleBaseProperty::set_date(const std::time_t& date_new)
{
    date = date_new;
    return *this;
}

ArticleBaseProperty& ArticleBaseProperty::set_description(const std::string& description_new)
{
    description = description_new;
    return *this;
}

ArticleBaseProperty& ArticleBaseProperty::set_fulltext(const std::string& fulltext_new)
{
    fulltext = fulltext_new;
    return *this;
}

std::unique_ptr<ArticlePropertyInterface> ArticleBaseProperty::copy_as_interface() const
{

    auto* cpy = new ArticleBaseProperty(title, url, rss_url, description);
    cpy->description = description;
    cpy->fulltext = fulltext;

    return std::unique_ptr<ArticlePropertyInterface>(cpy);
}

ArticleBaseProperty ArticleBaseProperty::copy() const noexcept
{
    return ArticleBaseProperty{this->title, this->url, this->rss_url, this->description};
}
