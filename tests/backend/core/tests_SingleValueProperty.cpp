//
// Created by parthu on 11/26/23.
//

#include "tests_SingleValueProperty.hpp"

/*!
 * \brief Test if SingleValueProperty<T,D>::copy_as_interface actually copies the value.
 */
TEST(SingleValueProperty, copy_as_interface)
{
    TestProperty prop("test");

    auto prop_copy = prop.copy_as_interface();
    auto prop_copy_casted = dynamic_cast<TestProperty*>(prop_copy.get());

    prop_copy_casted->set("test2");

    ASSERT_EQ(prop.get(), "test");
    ASSERT_EQ(prop_copy_casted->get(), "test2");
}


