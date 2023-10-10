cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

add_library(feedcat_backend
        article.cpp
        article.hpp
        rss/xml_parser.hpp
        rss/xml_parser.cpp
        rss/parser_fulltext.hpp
        rss/parser_fulltext_impl/Ntv.hpp
        helper/helper_tinyxml2.hpp
        helper/helper_tinyxml2.cpp
        db/article_database.cpp
        db/article_database.hpp)

target_compile_definitions(feedcat_backend PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_backend
        PUBLIC spdlog::spdlog
        PUBLIC cpr::cpr
        PUBLIC tinyxml2::tinyxml2
        PRIVATE sqlite_orm::sqlite_orm)