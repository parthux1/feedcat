
add_executable(feedcat_test_backend_core
    core/tests_ArticlePropertyHash.cpp
    core/tests_SingleValueProperty.cpp

)

target_link_libraries(feedcat_test_backend_core
    feedcat_core
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(feedcat_test_backend_core)