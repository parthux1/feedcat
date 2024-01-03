//
// Created by parthu on 11/26/23.
//
#include "tests_ArticlePropertyHash.hpp"

TEST(ArticlePropertyHash, hash_similar_ptr)
{
    ArticleBaseProperty dummy_property{"", "","", ""};
    ASSERT_EQ(ArticlePropertyHash{&dummy_property}, ArticlePropertyHash{&dummy_property});
}

TEST(ArticlePropertyHash, hash_similar_ref)
{
    ArticleBaseProperty dummy_property{"", "","", ""};
    ASSERT_EQ(ArticlePropertyHash{dummy_property}, ArticlePropertyHash{dummy_property});
}

/*!
 * \brief Different Constructors have varying implementations finally using typeid. Check if correct values are stored.
 */
TEST(ArticlePropertyHash, hash_similar_between_constructors)
{
    // Setup
    ArticleBaseProperty dummy_property{"", "","", ""};

    const ArticlePropertyHash hash_from_class = ArticlePropertyHash::create<ArticleBaseProperty>();
    const ArticlePropertyHash hash_from_ptr{&dummy_property};
    const ArticlePropertyHash hash_from_ref{&dummy_property};

    const auto std_hash_from_class = std::hash<ArticlePropertyHash>{}(hash_from_class);
    const auto std_hash_from_ptr = std::hash<ArticlePropertyHash>{}(hash_from_ptr);
    const auto std_hash_from_ref = std::hash<ArticlePropertyHash>{}(hash_from_ref);

    // check our Hash container
    ASSERT_EQ(hash_from_ref, hash_from_ptr);
    ASSERT_EQ(hash_from_class, hash_from_ref);

    // std:: Hash container
    ASSERT_EQ(std_hash_from_ref, std_hash_from_ptr);
    ASSERT_EQ(std_hash_from_class, std_hash_from_ptr);
}



