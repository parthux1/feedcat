//
// Created by parthu on 10/5/23.
//
#include "database_sqlite.hpp"

std::shared_ptr<DatabaseSqlLite> DatabaseSqlLite::getInstance(){
    // meyers singleton
    static auto instance = std::atomic{std::shared_ptr<DatabaseSqlLite>(new DatabaseSqlLite())};
    return instance;
}
