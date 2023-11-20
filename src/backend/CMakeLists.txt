cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(db)

set(feedcat_properties
        properties/ArticleBaseProperty.hpp
        properties/ArticleBaseProperty.cpp
)

set(feedcat_fulltext_parser
        network/fulltextImpl/Ntv.hpp
        network/fulltextImpl/Ntv.cpp
)

add_library(feedcat_backend
        ArticlePropertyInterface.hpp
        ArticlePropertyInterface.cpp
        ArticlePropertyHash.hpp
        ArticlePropertyHash.cpp
        Article.cpp
        Article.hpp
        Provider.hpp
        Provider.cpp
        Feed.hpp
        Feed.cpp

        helper/helper_tinyxml2.hpp
        helper/helper_tinyxml2.cpp

        db/database_interface.hpp
        db/database_interface.cpp

        network/FullTextParserStrategy.hpp
        network/parser_rss.hpp
        network/parser_rss.cpp

        ${feedcat_properties}
        ${feedcat_fulltextParser}
)

target_include_directories(feedcat_backend PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        .)

target_compile_definitions(feedcat_backend PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_backend
        PUBLIC spdlog::spdlog
        PUBLIC cpr::cpr
        PUBLIC tinyxml2::tinyxml2
        # PUBLIC feedcat_db
)