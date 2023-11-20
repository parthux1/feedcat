//
// Created by parthu on 11/18/23.
//
#pragma once

#include <string>
#include <optional>

namespace RSS
{

    /* TODO: If this class has no other use than the get_fulltext method, make a FullTextParserStrategy initializable via function pointer.
     * Currently the class provides no constraint
     */

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
