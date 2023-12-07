//
// Created by parthu on 11/26/23.
//

#include "tests_SingleValueProperty.hpp"

/*!
 * \brief Test if SingleValueProperty<T,D>::copy_as_interface actually copies the value.
 */
TEST(SingleValueProperty, copy_as_interface)
{
    TestStringProperty prop("test");

    std::unique_ptr<ArticlePropertyInterface> prop_copy = prop.copy_as_interface();
    auto prop_copy_casted = dynamic_cast<TestStringProperty*>(prop_copy.get());
    prop_copy_casted->set("test2");

    ASSERT_EQ(prop.get(), "test");
    ASSERT_EQ(prop_copy_casted->get(), "test2");
}

TEST(SingleValueProperty, different_hash_for_different_type)
{
    TestStringProperty prop("test");
    TestIntProperty prop2(1);

    ASSERT_NE(ArticlePropertyHash{prop}, ArticlePropertyHash{prop2});
}

TEST(SingleValueProperty, different_hash_for_same_stored_type)
{
    TestStringProperty prop("test");
    TestString2Property prop2("test");

    ASSERT_NE(ArticlePropertyHash{prop}, ArticlePropertyHash{prop2});
}