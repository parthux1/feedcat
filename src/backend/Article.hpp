//
// Created by parthu on 8/29/23.
//
#pragma once

#include <memory>
#include <unordered_map>

#include <ArticlePropertyInterface.hpp>


class Article
{
public:
    std::unordered_map<std::string, std::unique_ptr<ArticlePropertyInterface>> properties{};
};

/*
namespace RSS {

    class Article {
    public:
        [[nodiscard]] std::string to_string() const;

        bool operator==(const Article& other) const;

        // Members
    public:
        StringProperty url{"url"};
        std::string title;
        std::string description;
        std::optional<std::string> fulltext = {};
        std::string date;
        std::string rss_source;

        // how to have optional & Nonoptional properties?
        std::vector<std::unique_ptr<ArticlePropertyInterface>> extensions = {};
    };
}
*/