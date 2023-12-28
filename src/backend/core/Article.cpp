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
        properties[hash] = property->copy_as_interface();
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


Article Article::copy() const
{
    return Article{*this};
}

Article Article::copy_except(std::vector<ArticlePropertyHash> hashes) const
{
    const auto base_hash = ArticlePropertyHash::create<ArticleBaseProperty>();

    const bool list_contains_base_hash = std::find(hashes.begin(), hashes.end(), base_hash) != hashes.end();
    if(list_contains_base_hash)
    {
        throw ArticleBasePropertyRequiredError("remove hash of ArticleBaseProperty from the list of hashes.");
    }

    const ArticleBaseProperty cp_base = this->get<ArticleBaseProperty>().value()->copy();
    Article cp{cp_base};

    for(const auto&[hash, property] : properties)
    {
        // not target?
        if(std::find(hashes.begin(), hashes.end(), hash) != hashes.end())
        {
            continue;
        }

        cp.add_property(property->copy_as_interface());
    }

    return cp;
}


Article Article::copy_only(std::vector<ArticlePropertyHash> hashes) const
{
    const auto base_hash = ArticlePropertyHash::create<ArticleBaseProperty>();

    const bool list_contains_base_hash = std::find(hashes.begin(), hashes.end(), base_hash) != hashes.end();
    if(!list_contains_base_hash)
    {
        throw ArticleBasePropertyRequiredError{"add hash of ArticleBaseProperty to the list of hashes."};
    }

    const ArticleBaseProperty cp_base = this->get<ArticleBaseProperty>().value()->copy();
    Article cp{cp_base};

    for(const auto& hash : hashes)
    {
        const auto property = this->get(hash);
        if(!property.has_value())
        {
            throw std::out_of_range{"hash does not exist in this article."};
        }

        cp.add_property(property.value()->copy_as_interface());
    }

    return cp;
}