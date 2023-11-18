//
// Created by parthu on 11/18/23.
//
#pragma once

#include <string>
#include <chrono>

namespace RSS
{
    class Url
    {
    public:
        /*!
         * \param url URL of a single RSS feed
         */
        Url(const std::string& url);

    // Members
    public:
        std::string url;
        std::time_t last_update = -1; // invalid point in time
    };
}
