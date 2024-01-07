/*
 * Created by parthu on 10/5/23.
 * SqlLite Singleton Implementation
*/
#pragma once

#include <string>
#include <spdlog/spdlog.h>
#include <core/db/database_interface.hpp>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/Database.h>

class DatabaseSqlLite : public DatabaseInterface
{
public:
    /*
     * \brief Initialize a SQLite Connector. Creates a new database if not existing
     */
    DatabaseSqlLite(std::string filename);

    bool has_id(const DatabaseID& id) const override;

    bool has_table(const SanitizedString& name) const override;

    std::list<DatabaseID> get_all_ids() const override;

protected:
    bool make_table(const SanitizedString& name, const SanitizedMapping& mapping) override;

    std::optional<DatabaseID> store_entry(const SanitizedString& table, const SanitizedValues& entry) override;

    std::optional<SerializedValues> load_entry(const SanitizedString& table, const SanitizedMapping& expected_mapping, const DatabaseID& id) override;

private:
    std::unique_ptr<SQLite::Database> db;
};