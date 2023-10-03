#pragma once
#include <rss/parser_fulltext.hpp>
namespace RSS
{
    class ProviderNTV : public RSS::ProviderStrategy{
    public:
        ProviderNTV(){};
    };

    // Specializations for get_fulltext
    template <>
    std::optional<std::string> ParserFulltext<ProviderNTV>::get_fulltext(const std::string& url)
    {

        const auto article = cpr::Get(cpr::Url{url});
        if(article.status_code != 200)
        {
            SPDLOG_WARN("Query of article {} didn't return 200.", url);
            return std::nullopt;
        }
        tinyxml2::XMLDocument doc;
        const auto error = doc.Parse(tinyxml2::strip_javascript(article.text).c_str());
        if(error != 0)
        {
            SPDLOG_WARN("Error while parsing {}: {}\nGet-Response:\n{}", url, error, article.text);
            return std::nullopt;
        }
        SPDLOG_DEBUG("entering get_first");
        // NTV stores information is several <p> tags in <div class="article__text">
        // TODO: doesnt work
        const auto div_node = tinyxml2::get_first_by_attribute(doc.RootElement(), "class", "article__text");
        SPDLOG_DEBUG("finished get_first");
        if(!div_node.has_value())
        {
            SPDLOG_WARN("Article {} doesn't match expected Pattern for N-TV.", url);
            return std::nullopt;
        }

        //grab add append all <p> tags
        std::string fulltext;
        const auto ps = tinyxml2::get_all_by_tag(div_node.value(), "p");
        SPDLOG_INFO("Found {} <p> tags", ps.size());
        for(const auto& p : ps)
        {
            fulltext += std::string(p->GetText()) + "\n";
        }

        return fulltext;
    }

}


