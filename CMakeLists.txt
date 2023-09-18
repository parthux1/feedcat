cmake_minimum_required(VERSION 3.25.1)

project(feedcat)

# 3rd party
find_package(cpr REQUIRED)

set(CMAKE_CXX_STANDARD 20)

set(FEEDCAT_SRC_BACKEND main.cpp
        src/rss/article.hpp src/rss/article.cpp
)

add_executable(feedcat ${FEEDCAT_SRC_BACKEND})
target_link_libraries(feedcat PRIVATE cpr::cpr)
