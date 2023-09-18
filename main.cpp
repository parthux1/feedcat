#include <cpr/cpr.h>
#include <spdlog/spdlog.h>

#include <rss/xml_parser.hpp>

int main() {
    spdlog::set_level(spdlog::level::debug);

    //query RSS feed
    cpr::Response r = cpr::Get(cpr::Url{"https://www.n-tv.de/politik/rss"});

    const auto res = RSS::XML::parse(r.text);

    SPDLOG_INFO("Got {} articles", res.size());

    for(const auto& article : res)
    {
        SPDLOG_INFO(article.to_string());
    }

    return 0;
}
