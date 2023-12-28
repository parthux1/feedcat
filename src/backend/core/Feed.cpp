//
// Created by parthu on 11/18/23.
//

#include "Feed.hpp"


Feed::Feed(const std::string& url)
    : url(url)
{
}

void Feed::update(const std::optional<std::shared_ptr<FullTextParserStrategy>>& strategy)
{
    auto res = RSS::Parser::parse(url);

    for(auto &article : res)
    {
        articles.push_back(std::move(article));
    }

    if(strategy.has_value())
    {
        SPDLOG_CRITICAL("Fulltext parsing not implemented yet!");
    }
    const auto now = std::chrono::system_clock::now();
    last_update = std::chrono::system_clock::to_time_t(now);
}

Feed::Feed(const Feed &other) {
    url = other.url;
    last_update = other.last_update;

    for(const auto& article : other.articles)
    {
        articles.push_back(article);
    }
}
