//
// Created by parthu on 11/26/23.
//
#pragma once

#include <SingleValueProperty.hpp>

class FulltextProperty : public SingleValueProperty<std::string, FulltextProperty>
{
    using SingleValueProperty<std::string, FulltextProperty>::SingleValueProperty;
};