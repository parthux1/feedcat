include(FetchContent)
FetchContent_Declare(sqliteOrm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
        GIT_TAG        v1.8.2
)

add_subdirectory(sqlite_orm)

# git submodules
set(CMAKE_POSITION_INDEPENDENT_CODE 1) # sometimes spdlog isn't compiled with -fPIC, this fixes it
add_subdirectory(spdlog)
add_subdirectory(cpr)
add_subdirectory(tinyxml2)