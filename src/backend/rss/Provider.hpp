#pragma once

#include <optional>
#include <vector>
#include <memory>

#include <rss/url.hpp>
#include <rss/FullTextParserStrategy.hpp>
#include <rss/parser_rss.hpp>

namespace RSS {

    class Provider
    {
        // Constructors & Destructors
    public:
        ~Provider() = default;

        Provider() = default;
        Provider(const std::vector<RSS::Url>& urls);
        Provider(const std::vector<RSS::Url>& urls, std::shared_ptr<FullTextParserStrategy> strategy);

        // Functions
    public:
        Provider& set_fulltext_strategy(std::shared_ptr<FullTextParserStrategy> strategy);
        Provider& set_urls(std::vector<RSS::Url>& urls);

        // Members
    public:
        std::vector<RSS::Url> urls = {};
    private:
        std::optional<std::shared_ptr<FullTextParserStrategy>> fulltext_strategy = std::nullopt;
    };
}