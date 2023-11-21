//
// Created by parthu on 11/19/23.
//

#include "ArticlePropertyHash.hpp"

ArticlePropertyHash::ArticlePropertyHash(std::size_t value)
        : value(value)
{

}

ArticlePropertyHash::ArticlePropertyHash(const ArticlePropertyInterface* property)
{
    value = typeid(property).hash_code();
}

bool ArticlePropertyHash::operator==(const ArticlePropertyHash &other) const
{
    return value == other.value;
}

bool ArticlePropertyHash::operator!=(const ArticlePropertyHash &other) const
{
    return !(*this == other);
}

const std::size_t &ArticlePropertyHash::get() const
{
    return value;
}


