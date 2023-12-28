#include <spdlog/spdlog.h>

#include <Feed.hpp>
#include <properties/ArticleBasePropertyDb.hpp>
int main()
{
    spdlog::set_level(spdlog::level::debug);

    Feed f{"https://www.n-tv.de/wirtschaft/rss"};
    f.update();
    auto& article = f.articles.front();

    SPDLOG_INFO("Got {} articles", f.articles.size());

    const auto base = article.get<ArticleBaseProperty>();
    if(!base)
    {
        SPDLOG_ERROR("ArticleBaseProperty not found");
        return 1;
    }

    if(!store_property(base.value(), nullptr))
    {
        SPDLOG_ERROR("Could not store property \"{}\". Is Concept PropertyDbStrategy fulfilled?", typeid(base.value()).name());
        return 1;
    }
}


