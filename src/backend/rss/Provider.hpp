#pragma once

#include <optional>
#include <string>

#include <rss/url.hpp>
#include <rss/FullTextParserStrategy.hpp>
namespace RSS {

    class Provider
    {
        // Constructors & Destructors
    public:
        ~Provider() = default;

        Provider() = default;
        Provider(std::vector<RSS::Url>& urls);

        // Functions
    public:
        Provider& set_fulltext_strategy(std::shared_ptr<FullTextParserStrategy> strategy);

        // Members
    public:
        std::vector<RSS::Url> urls = {};
    private:
        std::optional<std::shared_ptr<FullTextParserStrategy>> fulltext_strategy = std::nullopt;
    };
}