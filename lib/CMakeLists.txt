# git submodules
set(CMAKE_POSITION_INDEPENDENT_CODE 1) # sometimes spdlog isn't compiled with -fPIC, this fixes it
add_subdirectory(spdlog)
add_subdirectory(cpr)
add_subdirectory(tinyxml2)
add_subdirectory(SQLiteCpp)
