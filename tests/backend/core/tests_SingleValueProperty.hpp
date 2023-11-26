//
// Created by parthu on 11/26/23.
//

#pragma once
#include <gtest/gtest.h>
#include<SingleValueProperty.hpp>

class TestProperty : public SingleValueProperty<std::string, TestProperty>
{
    using SingleValueProperty<std::string, TestProperty>::SingleValueProperty;
};