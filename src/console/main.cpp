#include <spdlog/spdlog.h>

#include <core/Feed.hpp>
#include <core/properties/ArticleBasePropertyDb.hpp>
#include <extension/db_impl/database_sqlite.hpp>

int main()
{
    spdlog::set_level(spdlog::level::debug);
    /*
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
    */

    ArticleBaseProperty prop{"test-title", "test-url", "test-rss-url", "test-description"};
    Article a{prop};
    DatabaseSqlLite db{"test"};

    db.store_property<ArticleBaseProperty>(a);
}


