#pragma once
#include <rss/parser_fulltext.hpp>
namespace RSS
{
    class ProviderNTV : public ParserFulltext
    {
    protected:
        std::optional<std::string> get_fulltext_impl(const std::string &url) override;

        std::vector<std::string> get_known_urls_impl() const override;
    };
}


