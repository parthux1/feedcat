set(FEEDCAT_TEST_BACKEND_CORE_SOURCES
    core/tests_ArticlePropertyHash.hpp
    core/tests_ArticlePropertyHash.cpp
    core/tests_SingleValueProperty.hpp
    core/tests_SingleValueProperty.cpp
# DB
    core/db/tests_SanitizedString.hpp
    core/db/tests_SanitizedString.cpp
)

set(FEEDCAT_TEST_BACKEND_EXTENSION_SOURCES
        extension/sqlite/tests_store_load.hpp
        extension/sqlite/tests_store_load.cpp
)

add_executable(feedcat_test_backend
    ${FEEDCAT_TEST_BACKEND_CORE_SOURCES}
    ${FEEDCAT_TEST_BACKEND_EXTENSION_SOURCES}
)

target_link_libraries(feedcat_test_backend
    PUBLIC feedcat_extension
    PRIVATE GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(feedcat_test_backend)