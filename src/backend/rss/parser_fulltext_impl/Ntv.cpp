//
// Created by parthu on 10/18/23.
//
#include "Ntv.hpp"

std::optional<std::string> RSS::ProviderNTV::get_fulltext_impl(const std::string& url)
{

    const auto article = cpr::Get(cpr::Url{url});
    if(article.status_code != 200)
    {
        SPDLOG_WARN("Query of article {} didn't return 200.", url);
        return std::nullopt;
    }
    tinyxml2::XMLDocument doc;


    // strip useless tags / tags which would crash tinyxml2
    static const std::vector<std::string> tags_to_strip{
            "script", "link", "style", "meta", "base", "img", "source", "input"
    };

    std::string html_stripped = article.text;
    for(const auto& tag : tags_to_strip) html_stripped = tinyxml2::strip_tag(html_stripped, tag);

    const auto error = doc.Parse(html_stripped.c_str());
    if(error != 0)
    {
        SPDLOG_WARN("Error while parsing {}:\nError: {}\nContext: {}", url,doc.ErrorStr(), html_stripped);

        std::ofstream f_out;
        f_out.open("full.txt");
        f_out << article.text;
        f_out.close();
        return std::nullopt;
    }

    // NTV stores information is several <p> tags in <div class="article__text">
    const auto div_node = tinyxml2::get_first_by_attribute(doc.RootElement(), "class", "article__text");

    if(!div_node.has_value())
    {
        SPDLOG_WARN("Article {} doesn't match expected Pattern for N-TV.", url);
        return std::nullopt;
    }

    //grab add append all <p> tags
    std::string fulltext;
    const auto ps = tinyxml2::get_all_by_tag(div_node.value(), "p");
    SPDLOG_DEBUG("Found {} <p> tags", ps.size());
    for(const auto* p : ps)
    {
        if(p->GetText()) fulltext += std::string(p->GetText()) + "\n";
    }

    return fulltext;
}