//
// Created by parthu on 8/29/23.
//
#pragma once

#include <memory>
#include <unordered_map>
#include <optional>

#include <core/ArticlePropertyInterface.hpp>
#include <core/ArticlePropertyHash.hpp>
#include <core/properties/ArticleBaseProperty.hpp> // required because it contains basic article definitions

#include <core/exceptions/ArticleBasePropertyRequiredError.hpp>

class Article
{
public:
    /*!
     * \brief Creates an article
     * \param base_property required article properties
     */
    explicit Article(ArticleBaseProperty base_property);

    Article(const Article& other);


    Article& operator=(const Article& other) = default;

    // Property Management

    /*!
     * Add a property by taking ownership of it. If the property already exists it will be overwritten.
     * \param property Property to take ownership of
     * \return this instance
     */
    Article& add_property(std::unique_ptr<ArticlePropertyInterface> property);

    /*!
     * \return true if the property exists in this article.
     */
    bool has_property(const ArticlePropertyHash& hash) const;

    /*!
     * \brief Get a property by its hash.
     * \param hash property to get
     * \return non-owning property-pointer if it exists, otherwise std::nullopt
     */
    std::optional<ArticlePropertyInterface*> get(const ArticlePropertyHash& hash);

    /*!
    * \brief Get a property by its hash.
    * \param hash property to get
    * \return non-owning property-pointer if it exists, otherwise std::nullopt
     * \throws std::runtime_error if ArticleBaseProperty should be removed.
    */
    std::optional<const ArticlePropertyInterface*> get(const ArticlePropertyHash& hash) const;

    /*!
     * \brief Get a dynamic-casted property by its hash. Requires information about properties at compile time.
     * \tparam T property to get
     * \note std::optional<T&> does not exist but might be useful here
     * \return non-owning property-pointer if it exists, otherwise std::nullopt
     */
    template<typename T>
        requires std::derived_from<T, ArticlePropertyInterface>
    std::optional<T*> get()
    {
        const auto hash = ArticlePropertyHash::create<T>();
        if(!has_property(hash)) return std::nullopt;

        return dynamic_cast<T*>(properties.at(hash).get());
    }

    /*!
     * \brief Get a dynamic-casted property by its hash. Requires information about properties at compile time.
     * \tparam T property to get
     * \note std::optional<T&> does not exist but might be useful here
     * \returns non-owning property-pointer if it exists, otherwise std::nullopt
     */
    template<typename T>
    requires std::derived_from<T, ArticlePropertyInterface>
    std::optional<const T*> get() const
    {
        const auto hash = ArticlePropertyHash::create<T>();
        if(!has_property(hash)) return std::nullopt;

        return dynamic_cast<const T*>(properties.at(hash).get());
    }

    /*!
     * \brief Copy this article with all its properties
     */
    Article copy() const;

    /*!
     * \brief Copy this article with all its properties except the ones specified
     * \param hashes properties to exclude
     * \throws ArticleBasePropertyRequiredError if ArticleBaseProperty is in hashes.
     */
    Article copy_except(std::vector<ArticlePropertyHash> hashes) const;

    /*!
     * \brief Copy this article with only the specified properties
     * \param hashes properties to include
     * \throws std::runtime_error if a given hash is not a property of this article
     * \throws ArticleBasePropertyRequiredError if ArticleBaseProperty is not in hashes.
     */
    Article copy_only(std::vector<ArticlePropertyHash> hashes) const;

public:
    std::unordered_map<ArticlePropertyHash, std::unique_ptr<ArticlePropertyInterface>> properties{};
};