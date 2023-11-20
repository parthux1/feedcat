//
// Created by parthu on 11/18/23.
//

#include <Provider.hpp>

Provider::Provider(const std::vector<Feed>& feeds)
    : feeds(feeds)
{
}

Provider::Provider(const std::vector<Feed>& feeds, std::shared_ptr<FullTextParserStrategy> strategy)
    : feeds(feeds),
      fulltext_strategy(strategy)
{
}

Provider& Provider::set_fulltext_strategy(std::shared_ptr<FullTextParserStrategy>& strategy)
{
    fulltext_strategy = strategy;
    return *this;
}

Provider& Provider::set_feeds(std::vector<Feed>& new_feeds)
{
    feeds.clear();
    for(auto& feed : new_feeds)
    {
        feeds.push_back(feed);
    }

    return *this;
}