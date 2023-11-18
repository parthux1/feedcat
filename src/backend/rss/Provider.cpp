//
// Created by parthu on 11/18/23.
//

#include <rss/Provider.hpp>

RSS::Provider::Provider(const std::vector<RSS::Url>& urls)
    : urls(urls)
{
}

RSS::Provider::Provider(const std::vector<RSS::Url>& urls, std::shared_ptr<FullTextParserStrategy> strategy)
    : urls(urls),
      fulltext_strategy(strategy)
{
}

RSS::Provider& RSS::Provider::set_fulltext_strategy(std::shared_ptr<FullTextParserStrategy> strategy)
{
    fulltext_strategy = strategy;
    return *this;
}

RSS::Provider& RSS::Provider::set_urls(std::vector<RSS::Url>& new_urls)
{
    this->urls = new_urls;
    return *this;
}