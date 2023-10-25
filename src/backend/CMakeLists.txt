cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(db)

add_library(feedcat_backend
        article.cpp
        article.hpp
        rss/parser_rss.hpp
        rss/parser_rss.cpp
        rss/ProviderInterface.hpp
        rss/provider_implementation/Ntv.hpp
        rss/provider_implementation/Ntv.cpp
        helper/helper_tinyxml2.hpp
        helper/helper_tinyxml2.cpp
)

target_include_directories(feedcat_backend PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        .)

target_compile_definitions(feedcat_backend PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_backend
        PUBLIC spdlog::spdlog
        PUBLIC cpr::cpr
        PUBLIC tinyxml2::tinyxml2
        PUBLIC feedcat_db)