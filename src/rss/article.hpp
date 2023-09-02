//
// Created by parthu on 8/29/23.
//
#pragma once

#include <string>

namespace RSS {

    class Article {
    public:
        [[nodiscard]] std::string to_string() const;

        bool operator==(const Article& other) const;

        // Members
    public:
        std::string url;
        std::string title;
        std::string description;
        std::string date; // TODO: change this to a date type
    };

}
