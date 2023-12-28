cmake_minimum_required(VERSION 3.26)
set(CMAKE_CXX_STANDARD 20)

project(feedcat)

# config
set(SPDLOG_ACTIVE_LEVEL "SPDLOG_LEVEL_DEBUG")

# 3rd party
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)

# targets
add_subdirectory(${PROJECT_SOURCE_DIR}/src/backend)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/console)

add_subdirectory(${PROJECT_SOURCE_DIR}/src/tui)

# tests
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)