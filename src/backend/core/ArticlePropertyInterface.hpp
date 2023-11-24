//
// Created by parthu on 11/18/23.
//
#pragma once

#include <memory>

/*!
 * This class is used for virtual table generation for all ArticleProperties and for constrains throughout the code.
 * A derived class can be stored in an article
 * A derived class specializing/overloading templates in property_save_templates can be stored and retrieved from a database.
 *
 * \see Article.hpp
 * \see property_save_templates.hpp
 */
class ArticlePropertyInterface
{
public:

    [[nodiscard]] virtual std::unique_ptr<ArticlePropertyInterface> copy_as_interface() const = 0;

    // allow polymorphic destruction
    virtual ~ArticlePropertyInterface() = default;
};
