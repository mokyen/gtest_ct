# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Create test executable
add_executable(test_gtest_ct
    passing_tests.cpp)

# Link against GTest and your library
target_link_libraries(test_gtest_ct
    PRIVATE
    GTest::GTest
    GTest::Main
    GTest::gmock
    GTest::gmock_main
    gtest_ct)

# Add the test
add_test(NAME test_gtest_ct COMMAND test_gtest_ct)