//
// Created by parthu on 9/2/23.
//

#include "parser_rss.hpp"

#include <utility>

using namespace RSS;

// Static leaked function
std::vector<Article> Parser::parse(const std::string& url) {
    tinyxml2::XMLDocument doc;
    doc.Parse(url.c_str());

    RSSVisitor parser{url, false};
    doc.Accept(&parser);

    const auto articles = parser.get_articles();

    return articles;
}

// internal parser implementation
Parser::RSSVisitor::RSSVisitor(std::string  url, bool exit_on_failure)
    : XMLVisitor(),
      exit_on_failure(exit_on_failure),
      url(std::move(url))
{
}

bool Parser::RSSVisitor::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute)
{
    // RSS 2.0 can be parsed like this
    if(element.Name() == std::string("item")) // cast needed
    {
        std::optional<Article> article = get_article(element);

        if(!article.has_value())
        {
            skips++;
            return !exit_on_failure;
        }

        articles.push_back(article.value());
    }
    return true;
}

std::optional<Article> Parser::RSSVisitor::get_article(const tinyxml2::XMLElement &element) noexcept
{
    Article article;

    const static std::unordered_map<std::string, std::string&> tags = {
        {"title", article.title},
        {"link", article.url},
        {"description", article.description},
        {"pubDate", article.date}
    };

    for(const auto&[tag, target_location] : tags)
    {
        const tinyxml2::XMLElement* xml_node = element.FirstChildElement(tag.c_str());

        if(xml_node == nullptr || xml_node->GetText() == nullptr)
        {
            SPDLOG_DEBUG("Article is missing Tag:{}", tag);
            return std::nullopt;
        }

        target_location = xml_node->GetText();
    }
    article.rss_source = url;
    return article;
}

const std::vector<Article>& Parser::RSSVisitor::get_articles() const noexcept
{
    if(skips > 0) SPDLOG_WARN("While parsing {} articles where skipped.", skips);
    return articles;
}
