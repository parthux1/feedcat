//
// Created by parthu on 9/2/23.
//

#include "parser_rss.hpp"

using namespace RSS;

// Static leaked function
std::vector<Article> XML::parse(const std::string &xml, const std::optional<std::string>& rss_source) {
    tinyxml2::XMLDocument doc;
    doc.Parse(xml.c_str());

    ParserRSS parser{false, rss_source};
    doc.Accept(&parser);
    return parser.get_articles();
}

// internal parser implementation

XML::ParserRSS::ParserRSS(bool exit_on_failure, const std::optional<std::string>& rss_source)
    : XMLVisitor(),
      exit_on_failure(exit_on_failure)
{
    if(rss_source.has_value()) this->rss_source = rss_source.value();
}

bool XML::ParserRSS::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute)
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

std::optional<Article> XML::ParserRSS::get_article(const tinyxml2::XMLElement &element) noexcept
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
    article.rss_source = rss_source;
    return article;
}

const std::vector<Article>& XML::ParserRSS::get_articles() const noexcept
{
    if(skips > 0) SPDLOG_WARN("While parsing {} articles where skipped.", skips);
    return articles;
}
