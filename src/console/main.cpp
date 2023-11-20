#include <spdlog/spdlog.h>

#include <Feed.hpp>

int main()
{
    spdlog::set_level(spdlog::level::debug);

    Feed f{"https://www.n-tv.de/wirtschaft/rss"};
    f.update();

    SPDLOG_INFO("Article Count: {}", f.articles.size());
}


