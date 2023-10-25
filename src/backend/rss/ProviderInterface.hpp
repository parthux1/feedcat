#pragma once

#include <optional>
#include <string>
#include <concepts>

#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <tinyxml2.h>
#include <helper/helper_tinyxml2.hpp>

#include <article.hpp>

namespace RSS {

    class ProviderInterface
    {
    public:
        virtual ~ProviderInterface() = default;

        /*!
         * \brief get fulltext from an url
         * \param url query fulltext from this url
         */
        std::optional<std::string> get_fulltext(const std::string& url) // currently no reason to use NVI here
        {
            return get_fulltext_impl(url);
        }

        /*!
         * \brief Insert fulltext of an article
         * \returns true if fulltext was added
         */
        bool get_fulltext(Article& article)
        {
            const auto fulltext = get_fulltext_impl(article.url);
            if(!fulltext.has_value())
            {
                return false;
            }
            article.fulltext = fulltext;
            return true;
        }

        /*!
         * \returns list of known urls which can be resolved by this parser
         */
        virtual std::vector<std::string> get_known_urls() const = 0;

    protected:
        virtual std::optional<std::string> get_fulltext_impl(const std::string& url)
        {
            SPDLOG_INFO("This Provider doesn't supply a function for resolving article contents. URL: {}.", url);
            return std::nullopt;
        };
    };

}