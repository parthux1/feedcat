SET(CMAKE_CXX_STANDARD_REQUIRED 20)

add_executable(feedcat_console main.cpp)

target_link_libraries(feedcat_console
        PUBLIC feedcat_core
        PUBLIC feedcat_extension)

target_include_directories(feedcat_console PUBLIC
        ${PROJECT_SOURCE_DIR}/src/backend)