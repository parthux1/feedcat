//
// Created by parthu on 11/19/23.
//

#include "ArticlePropertyHash.hpp"

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


