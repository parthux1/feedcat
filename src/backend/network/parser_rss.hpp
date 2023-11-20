//
// Created by parthu on 9/2/23.
//
#pragma once

#include <vector>
#include <optional>

#include <tinyxml2.h>
#include <spdlog/spdlog.h>
#include <cpr/cpr.h>

#include <article.hpp>
#include <rss/Provider.hpp>

namespace RSS::Parser
{
    /*!
     * \brief Parse a RSS XML File
     * \param url URL to get RSS feed from
     * \return a vector of articles
     */
    std::vector<Article> parse(const std::string& url);

    namespace
    {
        /*!
         * \brief Parses an RSS 2.0 feed. See https://de.wikipedia.org/wiki/RSS_(Web-Feed) for an example.
         * \note feed cache needs to be cleared manually
         */
        class RSSVisitor : public tinyxml2::XMLVisitor
        {
        public:
            /*!
             * \param url URL to get RSS feed from
             * \param exit_on_failure if true exists if an article can't be parsed, otherwise skips the article.
             */
            RSSVisitor(std::string  url, bool exit_on_failure = false);

            bool VisitEnter(const tinyxml2::XMLElement &, const tinyxml2::XMLAttribute *) override;

            [[nodiscard]] const std::vector<Article>& get_articles() const noexcept;

        private:
            std::optional<Article> get_article(const tinyxml2::XMLElement& element) noexcept;

            // Members
        private:
            bool exit_on_failure;
            const std::string url;
            unsigned int skips = 0;
            std::vector<Article> articles;
        };
    }
}
