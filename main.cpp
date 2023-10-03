#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <rss/xml_parser.hpp>
#include <rss/parser_fulltext_impl/Ntv.hpp>
#include <ostream>
int main() {
    spdlog::set_level(spdlog::level::debug);

    //query RSS feed
    // ntv: "https://www.n-tv.de/politik/rss"
    // heise: "https://www.heise.de/rss/heise-Rubrik-IT.rdf"
    cpr::Response r = cpr::Get(cpr::Url{"https://www.n-tv.de/politik/rss"});

    const auto res = RSS::XML::parse(r.text);

    SPDLOG_INFO("Got {} articles", res.size());

    SPDLOG_INFO("First article: {}", res[0].title);

    RSS::ParserFulltext<RSS::ProviderNTV> p_ntv;
    const auto fulltext = p_ntv.get_fulltext(res[0].url);
    if(fulltext.has_value()) SPDLOG_INFO(fulltext.value());
    return 0;
}
