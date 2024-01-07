//
// Created by parthu on 1/2/24.
//

#include "tests_store_load.hpp"

TEST(DatabaseSqlLite, store_load)
{
    const ArticleBaseProperty prop{"test-title", "test-url", "test-rss-url", "test-description"};
    const Article article{prop};

    DatabaseSqlLite db{"test"};
    const auto id = db.store_property<ArticleBaseProperty>(article);
    ASSERT_TRUE(id.has_value()) << "Could not store property";

    const auto loaded_prop = db.load_property<ArticleBaseProperty>(id.value());
    ASSERT_TRUE(loaded_prop.has_value()) << "Could not load property";

    ASSERT_EQ(prop, loaded_prop);
}