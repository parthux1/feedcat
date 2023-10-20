#pragma once

#include <optional>
#include <string>
#include <concepts>

#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <tinyxml2.h>
#include <helper/helper_tinyxml2.hpp>

#include <article.hpp>

/* To implement a fulltext parser
 * a) inherit from ParserFullText - NV Interface
 * b) implement _impl functions
*/


namespace RSS {

    class ParserFulltext
    {
    public:
        virtual ~ParserFulltext() = default;

        /*!
         * \brief get fulltext from an url
         * \param url query fulltext from this url
         */
        std::optional<std::string> get_fulltext(const std::string& url)
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
                SPDLOG_WARN("Couldn't get fulltext for article {}", article.url);
                return false;
            }
            article.fulltext = fulltext;
            return true;
        }

        /*!
         * \returns list of known urls which can be resolved by this parser
         */
        std::vector<std::string> get_known_urls() const
        {
            return get_known_urls_impl();
        }

    protected:
        virtual std::optional<std::string> get_fulltext_impl(const std::string& url) = 0;

        virtual std::vector<std::string> get_known_urls_impl() const = 0;
    };

}