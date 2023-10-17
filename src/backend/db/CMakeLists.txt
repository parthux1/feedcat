cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

add_library(feedcat_db
        database_interface.hpp
        database_interface.cpp
)

target_include_directories(feedcat_db PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        .)

target_compile_definitions(feedcat_db PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_db
        PUBLIC spdlog::spdlog
        PRIVATE SQLiteCpp)