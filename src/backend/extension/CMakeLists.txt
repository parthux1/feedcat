
# put non-core properties
set(FEEDCAT_PROPERTIES_SRC
)

# put database implementations here
set(FEEDCAT_DB_SRC
        db_impl/database_sqlite.hpp
        db_impl/database_sqlite.cpp
)

# put fulltext parser implementations here
set(FEEDCAT_FULLTEXT_SRC
        fulltextparser_impl/Ntv.hpp
        fulltextparser_impl/Ntv.cpp
)

add_library(feedcat_extension
        #${FEEDCAT_PROPERTIES_SRC}
        ${FEEDCAT_DB_SRC}
        ${FEEDCAT_FULLTEXT_SRC}
)

target_include_directories(feedcat_extension
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/SQLiteCpp/include
)

target_link_libraries(feedcat_extension
        PUBLIC SQLiteCpp
        PUBLIC sqlite3
        PUBLIC feedcat_core
)