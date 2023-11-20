//
// Created by parthu on 11/18/23.
//
#pragma once

#include <memory>
#include <db/database_interface.hpp>

class ArticlePropertyInterface
{
public:
    virtual bool store(DatabaseInterface* db) const = 0;

    virtual bool load(const DatabaseInterface* db) = 0;

    [[nodiscard]] virtual std::unique_ptr<ArticlePropertyInterface> copy() const = 0;

    // allow polymorphic destruction
    virtual ~ArticlePropertyInterface() = default;
};
