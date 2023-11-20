//
// Created by parthu on 8/29/23.
//

#include "Article.hpp"

Article::Article(ArticleBaseProperty base_property)
{
    ArticlePropertyHash hash{&base_property};
    properties[hash] = std::make_unique<ArticleBaseProperty>(std::move(base_property));
}

Article::Article(const Article &other)
{
    for(const auto& [hash, property] : other.properties)
    {
        properties[hash] = property->copy();
    }
}

Article& Article::add_property(std::unique_ptr<ArticlePropertyInterface> property)
{
    ArticlePropertyHash hash{property.get()};
    properties[hash] = std::move(property);
    return *this;
}

bool Article::has_property(const ArticlePropertyHash& hash) const
{
    return properties.contains(hash);
}

std::optional<ArticlePropertyInterface*> Article::get(const ArticlePropertyHash& hash)
{
    if(!has_property(hash)) return std::nullopt;

    return properties.at(hash).get();
}

std::optional<const ArticlePropertyInterface*> Article::get(const ArticlePropertyHash &hash) const
{
    if(!has_property(hash)) return std::nullopt;

    return properties.at(hash).get();
}
