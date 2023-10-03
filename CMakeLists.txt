cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

project(feedcat)

# config
set(SPDLOG_ACTIVE_LEVEL "SPDLOG_LEVEL_DEBUG")

message("===options===")
message("SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL}")
message("==============")
# 3rd Party
set(CMAKE_POSITION_INDEPENDENT_CODE 1) # sometimes spdlog isn't compiled with -fPIC, this fixes it
add_subdirectory(lib/spdlog)
add_subdirectory(lib/cpr)
add_subdirectory(lib/tinyxml2)


include_directories(${PROJECT_SOURCE_DIR}/src)

add_library(feedcat_lib
        src/rss/article.cpp
        src/rss/article.hpp
        src/rss/xml_parser.hpp
        src/rss/xml_parser.cpp
        src/rss/parser_fulltext.hpp
        src/rss/parser_fulltext_impl/Ntv.hpp
        src/helper/helper_tinyxml2.hpp
        src/helper/helper_tinyxml2.cpp)

target_compile_definitions(feedcat_lib PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_lib PUBLIC
        spdlog::spdlog
        cpr::cpr
        tinyxml2::tinyxml2)

add_executable(feedcat_backend main.cpp)
target_link_libraries(feedcat_backend feedcat_lib)
