//
// Created by parthu on 9/2/23.
//

#include "parser_rss.hpp"

#include <utility>

using namespace RSS;

// Static leaked function
std::vector<Article> Parser::parse(const std::string& url) {

    cpr::Response r = cpr::Get(cpr::Url{url});

    tinyxml2::XMLDocument doc;
    doc.Parse(r.text.c_str());

    RSSVisitor parser{url, false};
    doc.Accept(&parser);

    const auto articles = parser.get_articles();

    return articles;
}

// internal parser implementation
Parser::RSSVisitor::RSSVisitor(std::string url, bool exit_on_failure)
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


    std::string article_title, article_url, article_description, article_date;

    // XML Tags we want to extract
    const static std::unordered_map<std::string, std::string&> tags = {
        {"title", article_title},
        {"link", article_url},
        {"description", article_description},
        {"pubDate", article_date}
    };

    for(const auto&[tag, target_location] : tags)
    {
        const tinyxml2::XMLElement* xml_node = element.FirstChildElement(tag.c_str());

        if(xml_node == nullptr || xml_node->GetText() == nullptr)
        {
            SPDLOG_ERROR("Article is missing Tag:{}", tag);
            // continue if we handle an optional value e.g. pubDate
            return std::nullopt;
        }

        target_location = xml_node->GetText();
    }

    ArticleBaseProperty article_base{article_title, article_url, url, article_date};
    article_base.set_description(article_description);

    Article article{article_base};

    // TODO: Ticket #10 - parse date formats
    article.add_property(std::make_unique<DateProperty>(std::time_t{}));

    return article;
}

const std::vector<Article>& Parser::RSSVisitor::get_articles() const noexcept
{
    if(skips > 0) SPDLOG_WARN("While parsing {} articles where skipped.", skips);
    return articles;
}
