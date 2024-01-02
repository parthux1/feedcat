cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

add_library(feedcat_core
# base classes
        Article.cpp
        Article.hpp
        Feed.hpp
        Feed.cpp
        Provider.hpp
        Provider.cpp
        ArticlePropertyHash.hpp
        ArticlePropertyHash.cpp
# helper & namespaces
        helper/helper_tinyxml2.hpp
        helper/helper_tinyxml2.cpp
        network/parser_rss.hpp
        network/parser_rss.cpp
# Interfaces & Strategies
        ArticlePropertyInterface.hpp
        network/FullTextParserStrategy.hpp
        SingleValueProperty.hpp
# DB
        db/database_interface.hpp
        db/database_interface.cpp
        db/database_types.hpp
        db/property_serialize_functions.hpp
        db/SanitizedString.hpp
        db/SanitizedString.cpp
# core-required properties
        properties/ArticleBaseProperty.hpp
        properties/ArticleBaseProperty.cpp
        properties/ArticleBasePropertyDb.hpp
        properties/fulltext/FulltextProperty.hpp
        properties/fulltext/FulltextPropertyDb.hpp
        properties/date/DateProperty.hpp
        properties/date/DatePropertyDb.hpp
# exceptions
        exceptions/ArticleBasePropertyRequiredError.hpp
)

target_include_directories(feedcat_core
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/cpr/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/spdlog/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/tinyxml2/include
        PUBLIC  ${CMAKE_SOURCE_DIR}/src/backend
)

target_compile_definitions(feedcat_core PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})


target_link_libraries(feedcat_core
        PUBLIC spdlog::spdlog
        PUBLIC cpr::cpr
        PUBLIC tinyxml2
)