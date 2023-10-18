#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <rss/xml_parser.hpp>
#include <rss/parser_fulltext_impl/Ntv.hpp>
#include <db/database_sqlite.hpp>

int main() {
    spdlog::set_level(spdlog::level::info);

    //query RSS feed
    // ntv: "https://www.n-tv.de/politik/rss"
    // heise: "https://www.heise.de/rss/heise-Rubrik-IT.rdf"
    cpr::Response r = cpr::Get(cpr::Url{"https://www.n-tv.de/politik/rss"});

    auto res = RSS::XML::parse(r.text);

    SPDLOG_INFO("Got {} articles. Querying fulltext", res.size());
    RSS::ParserFulltext<RSS::ProviderNTV> p_ntv;

    for(auto& a : res)
    {
        if(!RSS::ParserFulltext<RSS::ProviderNTV>::get_fulltext(a))
        {
            SPDLOG_CRITICAL("Download of article {} failed.", a.title);
        }
    }
    std::size_t count = 0;
    SPDLOG_INFO("Saving to database.");
    auto db = DatabaseSqlLite::get_instance();
    for(const auto& a : res)
    {
        if(!db->article_exists(a))
        {
            db->store_article(a);
            count++;
        }
    }
    SPDLOG_INFO("Saved {} new articles to database.", count);

    return 0;
}
