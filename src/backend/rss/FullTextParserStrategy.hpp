//
// Created by parthu on 11/18/23.
//
#pragma once

#include <string>
#include <optional>

namespace RSS
{
    class FullTextParserStrategy
    {
    public:
        /*!
         * \brief Returns the fulltext of the article at the given url.
         * \param article_url
         */
        virtual std::optional<std::string> get_fulltext(const std::string &article_url) const = 0;
    };
}
