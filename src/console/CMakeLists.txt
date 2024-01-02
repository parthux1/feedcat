SET(CMAKE_CXX_STANDARD_REQUIRED 20)

add_executable(feedcat_console main.cpp)

target_link_libraries(feedcat_console
        PRIVATE feedcat_extension)