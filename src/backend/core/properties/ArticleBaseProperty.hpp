//
// Created by parthu on 11/19/23.
//
#pragma once

#include <spdlog/spdlog.h>

#include <optional>
#include <memory>
#include <string>

#include <ArticlePropertyInterface.hpp>


class ArticleBaseProperty : public ArticlePropertyInterface
{
public:
    /*!
     * \brief Constructs a new ArticleBaseProperty with minial required values.
     * @param title Title of the article
     * @param url URL to the article
     * @param rss_url RSS Feed URL
     * @param description RSS Description
     */
    ArticleBaseProperty(std::string title, std::string url, std::string rss_url, std::string description);

public:
    // Builder-Pattern
    //TODO: use copy-and-move instead of reference-and-copy
    ArticleBaseProperty& set_url(const std::string& url);

    ArticleBaseProperty& set_rss_url(const std::string& rss_url);

    ArticleBaseProperty& set_title(const std::string& title);

    ArticleBaseProperty& set_date(const std::time_t& date);

    ArticleBaseProperty& set_description(const std::string& description);

    ArticleBaseProperty& set_fulltext(const std::string& fulltext);

    bool operator==(const ArticleBaseProperty& other) const;

    [[nodiscard]] std::string to_string() const;

    // derived functions
public:
    std::unique_ptr<ArticlePropertyInterface> copy_as_interface() const override;

    ArticleBaseProperty copy() const noexcept;

public:
    // as defined in https://www.rssboard.org/rss-specification

    std::string url;
    std::string description = {};
    std::string rss_url;
    std::string title;

    // TODO: move these to custom properties
    std::optional<std::time_t> date;
    std::optional<std::string> fulltext = {};

};
