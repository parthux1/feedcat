/*
 * This file contains functions needed for database-property interaction
 *
 * Why not use an actual Strategy Pattern:
 * + static storage would allow registering consistent names for all properties.
 * - no static typeCheck for implemented Strategy bc. it accepts ArticlePropertyInterface*
 *   Could be done via visitor, but this would require a variant including all Property-Implementations
 *   A visitor can also be implemented via these free template functions
 */
#pragma once

#include <algorithm>
#include <string>
#include <optional>
#include <list>
#include <concepts>

#include <db/property_serialize_functions.hpp>
#include <ArticlePropertyInterface.hpp>


/*!
 * \brief Sanitizes table names of a SerizalizedMapping
 * \param mapping
 * \returns sanitized mapping
 */
SanitizedMapping sanitize(SerializedMapping& mapping);

/*!
 * \brief Sanitizes values of a SerializedValues
 * \param vals
 * \returns sanitized values
 */
SanitizedValues sanitize(SerializedValues& vals);

/*!
 * \brief Interface for simpler database interactions with custom connectors
 */
class DatabaseInterface
{
public:
    /*!
     * \brief Stores a property. Creates the corresponding table if it does not exist
     */
    template<PropertyIsStorable T>
    std::optional<DatabaseID> store_property(const T& property)
    {
        auto table = table_name<T>();
        sanitize(table);

        if(!has_table(table))
        {
            auto mapping = serialize_mapping<T>();
            append_ids(mapping);
            const auto mapping_s = sanitize(mapping);

            if(!make_table(table, mapping_s))
            {
                return std::nullopt;
            }
        }
        auto data = serialize(property);
        const auto data_s = sanitize(data);

        const auto res = store_entry(table, data_s);

        return res;
    }

    /*!
     * \brief Loads a property with the given id if possible
     */
    template<PropertyIsStorable T>
    std::optional<T> load_property(const DatabaseID& id)
    {
        auto table = table_name<T>();
        sanitize(table);
        const auto mapping = serialize_mapping<T>();
        const auto mapping_s = sanitize(mapping);

        const auto entry = load_entry(table, mapping_s, id);

        if(!entry)
        {
            SPDLOG_ERROR("Could not load entry with id {} from table {}", id, table);
            return std::nullopt;
        }

        const auto res = deserialize<T>(entry.value());
        return res;
    }

    /*!
     * \brief Checks if a property with the given id exists
     */
    virtual bool has_id(const DatabaseID& id) const = 0;

    /*!
     * \brief Checks if a table with the given name exists
     */
    virtual bool has_table(const std::string& name) const = 0;

    /*!
     * \brief Returns the number of stored properties
     */
    virtual std::list<DatabaseID> get_all_ids() const = 0;

protected:
    virtual bool make_table(const std::string& name, const SanitizedMapping & mapping) = 0;

    virtual std::optional<DatabaseID> store_entry(const std::string& table, const SanitizedValues & values) = 0;

    virtual std::optional<SerializedValues> load_entry(const std::string& table, const SanitizedMapping & expected_mapping, const DatabaseID& id) = 0;

private:
    /*!
     * \brief Add internal ID mappings to the given mapping
     * \returns a complete TableMapping for the given property
    */
    static void append_ids(SerializedMapping& mapping)
    {
        // TODO: better error handling. will crash if value already exists
        mapping.insert({"id_unique", DatabaseFieldType::PRIMARY_KEY});
    }
};