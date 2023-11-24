//
// Created by parthu on 11/24/23.
//

#pragma once

#include <stdexcept>
class ArticleBasePropertyRequiredError : public std::logic_error{
    using std::logic_error::logic_error;
};

