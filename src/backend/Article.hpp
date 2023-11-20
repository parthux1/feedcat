//
// Created by parthu on 8/29/23.
//
#pragma once

#include <memory>
#include <unordered_map>
#include <optional>

#include <ArticlePropertyInterface.hpp>
#include <ArticlePropertyHash.hpp>
#include <properties/ArticleBaseProperty.hpp> // required because it contains basic article definitions


class Article
{
public:
    /*!
     * \brief Creates an article
     * \param base_property required article properties
     */
    explicit Article(ArticleBaseProperty base_property);


    // Property Management

    /*!
     * Add a property by taking ownership of it. If the property already exists it will be overwritten.
     * \param property Property to take ownership of
     * @return this instance
     */
    Article& add_property(std::unique_ptr<ArticlePropertyInterface> property);

    /*!
     * @return true if the property exists in this article.
     */
    bool has_property(const ArticlePropertyHash& hash) const;

    /*!
     * \brief Get a property by its hash.
     * @param hash property to get
     * @return non-owning property-pointer if it exists, otherwise std::nullopt
     */
    std::optional<ArticlePropertyInterface*> get(const ArticlePropertyHash& hash);

    /*!
     * \brief Get a dynamic_pointer_casted property by its hash. Requires information about properties at compile time.
     * @tparam T property to get
     * @return non-owning property-pointer if it exists, otherwise std::nullopt
     */
    template<typename T>
        requires std::derived_from<T, ArticlePropertyInterface>
    std::optional<T> get()
    {
        const auto hash = ArticlePropertyHash::create<T>();
        if(!has_property(hash)) return std::nullopt;

        return std::dynamic_pointer_cast<T>(properties.at(hash).get());
    }


public:
    std::unordered_map<ArticlePropertyHash, std::unique_ptr<ArticlePropertyInterface>> properties{};
};