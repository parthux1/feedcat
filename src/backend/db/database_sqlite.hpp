/*
 * Created by parthu on 10/5/23.
 * SqlLite Singleton Implementation
*/
#pragma once

#include <atomic>
#include <mutex>
#include <memory>

#include <SQLiteCpp/SQLiteCpp.h>
#include <spdlog/spdlog.h>

#include "database_interface.hpp"

class DatabaseSqlLite : public DatabaseInterface
{
public:
    static std::shared_ptr<DatabaseSqlLite> get_instance();

    bool store_article(const RSS::Article& article) override;

    bool article_exists(const RSS::Article& url) const override;

    bool article_exists(const std::string& url) const override;

    std::optional<RSS::Article> get_article(std::string url) const override;

    std::size_t count_articles() const override;

    // Singleton behavior
    DatabaseSqlLite(const DatabaseSqlLite&) = delete;
    DatabaseSqlLite& operator=(const DatabaseSqlLite&) = delete;

    // leaked for static shared_ptr instance in get_instance()
    ~DatabaseSqlLite() = default;
private:
    /*!
     *
     * @param db_name name to open/create
     * @throws SQLite::Exception
     */
    DatabaseSqlLite(std::string db_name = "feedcat_db.sqlite3");

    // Members

    // Underlying Model will handle thread safety. You're not supposed to share this instance across threads.
    // TODO: is this actually thread save? The doc is not clear on this
    std::unique_ptr<SQLite::Database> db = nullptr;
};

