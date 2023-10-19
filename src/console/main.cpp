#include <chrono>
#include <thread>

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <rss/parser_rss.hpp>
#include <rss/parser_fulltext_impl/Ntv.hpp>
#include <db/database_sqlite.hpp>

void update_urls()
{
    //query RSS feed
    // ntv: "https://www.n-tv.de/politik/rss"
    // heise: "https://www.heise.de/rss/heise-Rubrik-IT.rdf"

    std::list<std::string> urls_ntv = {"https://www.n-tv.de/wirtschaft/rss", "https://www.n-tv.de/politik/rss"};
    auto db = DatabaseSqlLite::get_instance();
    RSS::ProviderNTV p_ntv{};

    for(const auto& url : urls_ntv)
    {
        SPDLOG_INFO("Refreshing {}", url);

        cpr::Response r = cpr::Get(cpr::Url{url});
        auto res = RSS::XML::parse(r.text);


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

    SPDLOG_INFO("Current db size: {} articles.", db->count_articles());
}

int main() {
    spdlog::set_level(spdlog::level::info);

    const std::size_t poll_interval = 1000 * 60 * 30; // 30min
    const std::chrono::milliseconds sleep_interval{10};
    std::size_t current = poll_interval;

    while(true)
    {

        std::this_thread::sleep_for(sleep_interval);
        current += sleep_interval.count(); // 1 tick = 1ms

        if(current >= poll_interval)
        {
            SPDLOG_INFO("Polling RSS feeds...");
            update_urls();
            current = 0;
            SPDLOG_INFO("Next poll in {} minutes.", poll_interval/1000/60);
        }
    }
}


