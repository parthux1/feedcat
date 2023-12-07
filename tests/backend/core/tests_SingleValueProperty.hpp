//
// Created by parthu on 11/26/23.
//

#pragma once
#include <gtest/gtest.h>
#include<SingleValueProperty.hpp>
#include<ArticlePropertyHash.hpp>

class TestStringProperty : public SingleValueProperty<std::string, TestStringProperty>
{
    using SingleValueProperty<std::string, TestStringProperty>::SingleValueProperty;
};

class TestString2Property : public SingleValueProperty<std::string, TestString2Property>
{
    using SingleValueProperty<std::string, TestString2Property>::SingleValueProperty;
};

class TestIntProperty : public SingleValueProperty<int, TestIntProperty>
{
    using SingleValueProperty<int, TestIntProperty>::SingleValueProperty;
};