//
// Created by parthu on 12/19/23.
//
#pragma once
#include <cstddef>
#include <variant>
#include <ctime>
#include <unordered_map>

using DatabaseID = std::size_t;

enum class DatabaseFieldType
{
    TEXT,
    NUMBER,
    TIMESTAMP,
    PRIMARY_KEY
};

using DatabaseField = std::variant<std::string, int, std::time_t, DatabaseID>;

using SerializedMapping = std::unordered_map<std::string, DatabaseFieldType>;
using SerializedValues = std::unordered_map<std::string, DatabaseField>;
