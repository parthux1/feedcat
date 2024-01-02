//
// Created by parthu on 11/18/23.
//
#pragma once

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>
#include <tinyxml2.h>

#include <core/network/FullTextParserStrategy.hpp>
#include <core/helper/helper_tinyxml2.hpp>

namespace RSS
{
    class Ntv : public FullTextParserStrategy
    {
    public:
        [[nodiscard]] std::optional<std::string> get_fulltext(const std::string &article_url) const override;
    };
}