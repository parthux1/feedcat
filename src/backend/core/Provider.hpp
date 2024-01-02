#pragma once

#include <optional>
#include <vector>
#include <memory>

#include <core/Feed.hpp>
#include <core/network/FullTextParserStrategy.hpp>
#include <core/network/parser_rss.hpp>

class Provider
{
public:
    Provider(const std::vector<Feed>& feeds);
    Provider(const std::vector<Feed>& feeds, std::shared_ptr<FullTextParserStrategy> strategy);

public:
    Provider& set_fulltext_strategy(std::shared_ptr<FullTextParserStrategy>& strategy);
    Provider& set_feeds(std::vector<Feed>& feeds);

public:
    std::vector<Feed> feeds = {};
private:
    std::optional<std::shared_ptr<FullTextParserStrategy>> fulltext_strategy = std::nullopt;
};