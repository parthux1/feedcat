//
// Created by parthu on 11/26/23.
//

#include <gtest/gtest.h>

#include <ArticlePropertyHash.hpp>
#include <properties/ArticleBaseProperty.hpp>

/*!
 * \brief Different Constructors have varying implementations finally using typeid. Check if correct values are stored.
 */
TEST(ArticlePropertyHash, DifferentConstructorComparison)
{
    // Setup
    ArticleBaseProperty dummy_property{"", "","", ""};

    const ArticlePropertyHash hash_from_class = ArticlePropertyHash::create<ArticleBaseProperty>();
    const ArticlePropertyHash hash_from_instance{&dummy_property};

    const auto std_hash_from_class = std::hash<ArticlePropertyHash>{}(hash_from_class);
    const auto std_hash_from_instance = std::hash<ArticlePropertyHash>{}(hash_from_instance);

    ASSERT_EQ(hash_from_class.get(), hash_from_instance.get());
    ASSERT_EQ(std_hash_from_class, std_hash_from_instance);
}