#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <rss/xml_parser.hpp>
#include <rss/parser_fulltext_impl/Ntv.hpp>
#include <ostream>
#include <thread>

int main() {
    spdlog::set_level(spdlog::level::info);

    //query RSS feed
    // ntv: "https://www.n-tv.de/politik/rss"
    // heise: "https://www.heise.de/rss/heise-Rubrik-IT.rdf"
    cpr::Response r = cpr::Get(cpr::Url{"https://www.n-tv.de/politik/rss"});

    auto res = RSS::XML::parse(r.text);

    SPDLOG_INFO("Got {} articles. Querying fulltext", res.size());
    RSS::ParserFulltext<RSS::ProviderNTV> p_ntv;

    //prepare multi-thread packages
    std::vector<RSS::Article> p1{res.begin(), res.begin()+(long)res.size()/2};
    std::vector<RSS::Article> p2{res.begin()+(long)res.size()/2, res.end()-1};

    auto ntv_download = [](std::vector<RSS::Article>& articles) -> void
    {
        for(auto& a : articles)
        {
            if(!RSS::ParserFulltext<RSS::ProviderNTV>::get_fulltext(a))
            {
                SPDLOG_CRITICAL("Download of article {} failed.", a.title);
            }

        }
    };

    std::jthread t1{ntv_download, std::ref(p1)};
    std::jthread t2{ntv_download, std::ref(p2)};

    t1.join();
    t2.join();

    // merge again
    p1.insert(p1.end(), std::make_move_iterator(p1.begin()), std::make_move_iterator(p1.end()));
    res = std::move(p1);

    SPDLOG_INFO("Saving fulltext of {} downloaded articles.", res.size());


    std::size_t count = 0;
    for(const auto& a : res)
    {
        if(a.fulltext.has_value())
        {
            std::ofstream f_out;
            const std::string file = fmt::format("ntv_out/{}.md", count);
            f_out.open(file);

            if(!f_out.is_open())
            {
                SPDLOG_CRITICAL("File {} couldn't be created.", file);
            }
            try{
                const std::string_view md_linebreak = "  \n";
                f_out << "##  " << a.title << std::endl;
                f_out << "Date: " << a.date << md_linebreak;
                f_out << "URL: " << a.url << md_linebreak;
                f_out << a.fulltext.value();
                f_out.close();
            }catch(std::exception& e)
            {
                SPDLOG_CRITICAL("Writing to file failed. Current Article: {}\nURL:{}", a.title, a.url);
            }
        }
        count++;
    }

    return 0;
}
