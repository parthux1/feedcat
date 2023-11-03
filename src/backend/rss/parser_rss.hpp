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
#include <rss/ProviderInterface.hpp>

namespace RSS::XML
{
    /*!
     * \brief Parse a RSS XML File
     * \param xml the xml file as string
     * \param rss_source the source of the RSS feed. If not set the source will be set to "unknown"
     * \return a vector of articles without fulltext
     */
    std::vector<Article> parse(const std::string& xml, const std::optional<std::string>& rss_source = std::nullopt);

    /*!
     * \brief Parse a RSS XML File. If parser is set fulltext queries will be launched for all articles!
     * \param url the url file to query
     * \param parser a fulltext parser. if not set the fulltext will be empty.
     * \return a vector of articles without fulltext
     * \throws std::runtime_error if url is not a known url for parser.
     * \note If performance matters execute the fulltext queries manually for interesting articles.
     */
    std::vector<Article> query_and_parse(const std::string& url, const std::unique_ptr<ProviderInterface>& parser = nullptr);

    namespace
    {
        /*!
         * \brief Parses an RSS 2.0 feed. See https://de.wikipedia.org/wiki/RSS_(Web-Feed) for an example.
         * \note feed cache needs to be cleared manually
         */
        class ParserRSS : public tinyxml2::XMLVisitor
        {
        public:
            /*!
             * \param rss_source the source of the RSS feed. If not set the source will be set to "unknown"
             * \param exit_on_failure if true exists if an article can't be parsed, otherwise skips the article.
             */
            ParserRSS(bool exit_on_failure = false, const std::optional<std::string>& rss_source_url = std::nullopt);

            bool VisitEnter(const tinyxml2::XMLElement &, const tinyxml2::XMLAttribute *) override;

            [[nodiscard]] const std::vector<Article>& get_articles() const noexcept;

        private:
            std::optional<Article> get_article(const tinyxml2::XMLElement& element) noexcept;

            // Members
        private:
            bool exit_on_failure;
            std::string rss_source = "unknown";
            unsigned int skips = 0;
            std::vector<Article> articles;
        };
    }
}
