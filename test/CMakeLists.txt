# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Create test executable
add_executable(test_gtest_ct
    passing_tests.cpp)

# Uncomment to see the output of the templates that are added in build/passing_tests.ii
# if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#     # -save-temps will keep all intermediate files, including .i or .ii files
#     target_compile_options(test_gtest_ct PRIVATE -save-temps)
# endif()

# Link against GTest and your library
target_link_libraries(test_gtest_ct
    PRIVATE
    GTest::GTest
    GTest::Main
    GTest::gmock
    GTest::gmock_main
    gtest_ct)

# Add the test
add_test(
    NAME test_gtest_ct
    COMMAND test_gtest_ct
    ENVIRONMENT GTEST_DEATH_TEST_STYLE=fast # Recommended style for robustness
)