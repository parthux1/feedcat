#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <rss/parser_rss.hpp>
#include <rss/parser_fulltext_impl/Ntv.hpp>
#include <db/database_sqlite.hpp>

int main() {
    spdlog::set_level(spdlog::level::info);

    //query RSS feed
    // ntv: "https://www.n-tv.de/politik/rss"
    // heise: "https://www.heise.de/rss/heise-Rubrik-IT.rdf"

    std::list<std::string> urls_ntv = {"https://www.n-tv.de/wirtschaft/rss", "https://www.n-tv.de/politik/rss"};

    for(const auto& url : urls_ntv)
    {
        SPDLOG_INFO("Refreshing {}", url);

        cpr::Response r = cpr::Get(cpr::Url{url});
        auto res = RSS::XML::parse(r.text);

        auto db = DatabaseSqlLite::get_instance();
        RSS::ProviderNTV p_ntv{};
        std::size_t count = 0;

        for(auto& a : res)
        {
            if(!db->article_exists(a))
            {
                if(p_ntv.get_fulltext(a))
                {
                    db->store_article(a);
                    count++;
                }
                else
                {
                    SPDLOG_WARN("failed to fetch fulltext of URL: {}", a.url);
                }
            }
        }
        SPDLOG_INFO("{}/{} articles were new and got saved to local database.", count, res.size());
    }
    return 0;
}
