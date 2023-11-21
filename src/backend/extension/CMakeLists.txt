
# put non-core properties
set(feedcat_properties
)

# put database implementations here
set(feedcat_db
        db_impl/database_sqlite.hpp
        db_impl/database_sqlite.cpp
)

# put fulltext parser implementations here
set(feedcat_fulltext_parser
        fulltextparser_impl/Ntv.hpp
        fulltextparser_impl/Ntv.cpp
)

add_library(feedcat_extension
        ${feedcat_properties}
        ${feedcat_db}
        ${feedcat_fulltext_parser}
)

target_include_directories(feedcat_extension
        PUBLIC ${CMAKE_SOURCE_DIR}/lib
        PUBLIC ${CMAKE_SOURCE_DIR}/backend/core)

target_link_libraries(feedcat_extension
        PUBLIC sqlite3
        PUBLIC feedcat_core
)