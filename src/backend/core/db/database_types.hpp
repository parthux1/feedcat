//
// Created by parthu on 12/19/23.
//
#pragma once
#include <cstddef>
#include <variant>
#include <ctime>
#include <unordered_map>

#include <core/db/SanitizedString.hpp>

using DatabaseID = std::size_t;

enum class DatabaseFieldType
{
    TEXT,
    NUMBER,
    TIMESTAMP,
    PRIMARY_KEY // primary keys are defined by the database. You don't need to add them to your mapping
};

using DatabaseField = std::variant<std::string, int, std::time_t, DatabaseID>;

using SerializedMapping = std::unordered_map<std::string, DatabaseFieldType>;
using SerializedValues = std::unordered_map<std::string, DatabaseField>;

using SanitizedMapping = std::unordered_map<SanitizedString, DatabaseFieldType>;
using SanitizedValues = std::unordered_map<SanitizedString, DatabaseField>;
