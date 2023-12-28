/*
 * Created by parthu on 10/5/23.
 * SqlLite Singleton Implementation
*/
#pragma once

#include <atomic>
#include <mutex>
#include <memory>

#include <spdlog/spdlog.h>

#include <db/database_interface.hpp>

#if false
class DatabaseSqlLite : public DatabaseInterface
{
    // Singleton behavior
public:
    DatabaseSqlLite(const DatabaseSqlLite&) = delete;
    DatabaseSqlLite& operator=(const DatabaseSqlLite&) = delete;

    // leaked for static shared_ptr instance in get_instance()
    ~DatabaseSqlLite() = default;

    static std::shared_ptr<DatabaseSqlLite> get_instance();

    // non-NVI overrides
public:
    bool store_article(const Article& article) override;

    std::optional<Article> get_article(std::string url) const override;

    std::size_t count_articles() const override;

    // NVI implementations
private:
    bool article_exists_impl(const std::string& url) const override;

    std::size_t update_article_impl(const std::string& url_old, const RSS::Article& article_new) override;

private:

    /*!
     * Create a new DB-Connection
     * @param db_name name to open/create
     * @throws SQLite::Exception
     */
    DatabaseSqlLite(std::string db_name = "feedcat_db.sqlite3");

    // Members

    // Underlying Model will handle thread safety. You're not supposed to share this instance across threads.
    // TODO: is this actually thread save? The doc is not clear on this
    std::unique_ptr<SQLite::Database> db = nullptr;
};

#endif