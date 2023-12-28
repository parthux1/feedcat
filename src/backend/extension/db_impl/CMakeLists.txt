set(CMAKE_CXX_STANDARD 20) # for stringview .endswith

add_library(feedcat_db
        database_interface.hpp
        database_interface.cpp
        database_sqlite.hpp
        database_sqlite.cpp
)

target_include_directories(feedcat_db PUBLIC
        ${CMAKE_SOURCE_DIR}/lib
        ${CMAKE_SOURCE_DIR}/lib/SQLiteCpp/include
        ${CMAKE_SOURCE_DIR}/src
        .)

target_compile_definitions(feedcat_db PUBLIC SPDLOG_ACTIVE_LEVEL=${SPDLOG_ACTIVE_LEVEL})

target_link_libraries(feedcat_db
        PUBLIC spdlog::spdlog
        PRIVATE SQLiteCpp)