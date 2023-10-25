#pragma once
#include <rss/ProviderInterface.hpp>
namespace RSS
{
    class ProviderNTV : public ProviderInterface
    {
    protected:
        std::optional<std::string> get_fulltext_impl(const std::string &url) override;

        std::vector<std::string> get_known_urls() const override;
    };
}


