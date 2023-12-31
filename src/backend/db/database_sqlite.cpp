//
// Created by parthu on 10/5/23.
//
#include "database_sqlite.hpp"

// Static access

std::shared_ptr<DatabaseSqlLite> DatabaseSqlLite::get_instance(){
    // meyers singleton
    static auto instance = std::shared_ptr<DatabaseSqlLite>(new DatabaseSqlLite());
    return instance;
}

DatabaseSqlLite::DatabaseSqlLite(std::string db_name)
{
    try
    {
        if (!db_name.ends_with(".sqlite3")) db_name.append(".sqlite3");
        db = std::make_unique<SQLite::Database>(SQLite::Database{db_name.data(), SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE});
        SPDLOG_DEBUG("{} opened.", db_name);

        const std::string create_table_article = "CREATE TABLE IF NOT EXISTS article(id INTEGER PRIMARY KEY ASC, url, title, description, fulltext, date, rss_source)";
        const bool success = db->tryExec(create_table_article);

        if(success) SPDLOG_DEBUG("Created article-table.");
    }
    catch (const std::exception &e)
    {
        SPDLOG_ERROR("Error opening database: {}", e.what());
        throw e;
    }
}

// public overrides

std::optional<RSS::Article> DatabaseSqlLite::get_article(std::string url) const
{
    if(!article_exists(url)) return std::nullopt;

    SQLite::Statement query(*db, "SELECT * FROM article WHERE url = ?");
    query.bind(1, url);

    // get first res
    query.executeStep();

    std::optional<std::string> fulltext = std::nullopt;
    if(!query.getColumn("fulltext").isNull()) fulltext = query.getColumn("fulltext");

    RSS::Article article{
            query.getColumn("url"),
            query.getColumn("title"),
            query.getColumn("description"),
            fulltext,
            query.getColumn("date"),
            query.getColumn("rss_source")
    };

    // we only expect one result
    if(query.executeStep())
    {
        std::size_t count = 2;
        while(query.executeStep()) count++;
        SPDLOG_WARN("Found {} entries for url {}. Returning first.", count, url);
    }

    return article;
}

std::size_t DatabaseSqlLite::count_articles() const
{
    SQLite::Statement query(*db, "SELECT COUNT(*) FROM article");
    query.executeStep();
    int result = query.getColumn(0);
    return result;
}

bool DatabaseSqlLite::store_article(const RSS::Article &article)
{
    SQLite::Statement query(*db, "INSERT INTO article VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.bind(1); // id autoincrement
    query.bind(2, article.url);
    query.bind(3, article.title);
    query.bind(4, article.description);

    if(article.fulltext.has_value()) query.bind(5, article.fulltext.value());
    else query.bind(5);

    query.bind(6, article.date);
    query.bind(7, article.rss_source);

    try
    {
        const int flag = query.exec();
        if(!flag) SPDLOG_WARN("Failed to store article: {}. Query returned: {}", article.url, flag);
        return flag;
    }catch (const std::exception& e)
    {
        SPDLOG_ERROR("Failed to store article: {}. Exception: {}", article.url, e.what());
        return false;
    }
}

// NVI implementations

bool DatabaseSqlLite::article_exists_impl(const std::string& url) const
{
    const std::string statement = "SELECT EXISTS(SELECT 1 FROM article WHERE url = ?)";
    SQLite::Statement query(*db, statement);

    try
    {
        query.bind(1, url);
        query.executeStep();
        int flag = query.getColumn(0);
        return flag;
    }catch (const std::exception& e)
    {
        SPDLOG_ERROR("Failed to check if article exists: {}. Exception: {}", url, e.what());

    }
    return false;
}

std::size_t DatabaseSqlLite::update_article_impl(const std::string& url_old, const RSS::Article& article_new)
{
    // get amount of entries updated
    SQLite::Statement query_count(*db, "SELECT COUNT(*) FROM article WHERE url = ?");
    query_count.bind(1, url_old);
    query_count.executeStep();

    std::size_t count = query_count.getColumn(0).getInt();

    if(count>1)
    {
        SPDLOG_WARN("Found {} entries for url {}. Updating all.", count, url_old);
    }


    // update all
    SQLite::Transaction t{*db};
    SQLite::Statement query(*db, "UPDATE article SET url=?, title=?, description=?, fulltext=?, date=?, rss_source=? WHERE url=?");
    const std::string fulltext = article_new.fulltext.has_value() ? article_new.fulltext.value() : "";

    query.bind(1, article_new.url);
    query.bind(2, article_new.url);
    query.bind(3, article_new.title);
    query.bind(4, article_new.description);
    query.bind(5, fulltext);
    query.bind(6, article_new.rss_source);
    query.bind(7, url_old);

    query.exec();
    t.commit();

    return count;
}
