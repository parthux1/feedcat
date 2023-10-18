//
// Created by parthu on 10/5/23.
//
#include "database_sqlite.hpp"

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

        const std::string create_table_article = "CREATE TABLE IF NOT EXISTS article(id INTEGER PRIMARY KEY ASC, url, title, description, fulltext, date)";
        const bool success = db->tryExec(create_table_article);

        if(success) SPDLOG_DEBUG("Created article-table.");
    }
    catch (const std::exception &e)
    {
        SPDLOG_ERROR("Error opening database: {}", e.what());
        throw e;
    }
}

bool DatabaseSqlLite::store_article(const RSS::Article &article)
{
    SQLite::Statement query(*db, "INSERT INTO article VALUES (?, ?, ?, ?, ?, ?)");
    query.bind(1); // id autoincrement
    query.bind(2, article.url);
    query.bind(3, article.title);
    query.bind(4, article.description);

    if(article.fulltext.has_value()) query.bind(5, article.fulltext.value());
    else query.bind(5);

    query.bind(6, article.date);

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

bool DatabaseSqlLite::article_exists(const RSS::Article& article)
{
    const std::string statement = "SELECT EXISTS(SELECT 1 FROM article WHERE url = ?)";
    SQLite::Statement query(*db, statement);

    try
    {
        query.bind(1, article.url);
        query.executeStep();
        int flag = query.getColumn(0);
        return flag;
    }catch (const std::exception& e)
    {
        SPDLOG_ERROR("Failed to check if article exists: {}. Exception: {}", article.url, e.what());

    }
    return false;
}