#pragma once

#include <optional>
#include <string>
#include <concepts>

#include <spdlog/spdlog.h>
#include <cpr/cpr.h>
#include <tinyxml2.h>
#include <helper/helper_tinyxml2.hpp>

#include <rss/article.hpp>
namespace RSS {

    class ProviderStrategy{};
    // force usage of derived class which can be used to specialize functions
    template<typename T>
    concept ExplicitMarkedAsProvider = std::derived_from<T, ProviderStrategy> && !std::is_same_v<T, ProviderStrategy>;

    /*!
     * Implement fulltext parsing for different newsletters
     */
    template <typename P>
    requires ExplicitMarkedAsProvider<P>
    class ParserFulltext
    {
    public:
        virtual ~ParserFulltext() = default;

        /*!
         * \brief get fulltext from an url
         * \param url query fulltext from this url
         */
        static std::optional<std::string> get_fulltext(const std::string& url)
        {
            SPDLOG_WARN("get_fulltext not implemented for provider {}", typeid(P).name());
            return std::nullopt;
        }

        /*!
         * \brief Insert fulltext of an article
         * \returns true if fulltext was added
         */
        static bool get_fulltext(Article& article)
        {
            const auto fulltext = get_fulltext(article.url);
            if(!fulltext.has_value())
            {
                SPDLOG_WARN("Couldn't get fulltext for article {}", article.url);
                return false;
            }
            article.fulltext = fulltext;
            return true;
        }

    };

}