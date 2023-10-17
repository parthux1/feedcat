/*
 * Created by parthu on 10/5/23.
 * SqlLite Singleton Implementation
*/
#pragma once

#include <atomic>
#include <mutex>
#include <memory>
#include <db/database_interface.hpp>

class DatabaseSqlLite : public DatabaseInterface
{
public:
    static std::shared_ptr<DatabaseSqlLite> getInstance();

    // Singleton behavior
    DatabaseSqlLite(const DatabaseSqlLite&) = delete;
    DatabaseSqlLite& operator=(const DatabaseSqlLite&) = delete;

    // leaked for static shared_ptr instance in getInstance()
    ~DatabaseSqlLite() = default;
private:
    DatabaseSqlLite() = default;
};

