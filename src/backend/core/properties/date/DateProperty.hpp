//
// Created by parthu on 12/7/23.
//
#pragma once

#include <ctime>
#include <SingleValueProperty.hpp>

class DateProperty : public SingleValueProperty<std::time_t, DateProperty>
{
    using SingleValueProperty<std::time_t, DateProperty>::SingleValueProperty;
};

