add_executable(test_gtest_ct
    passing_tests.cpp)

target_link_libraries(test_gtest_ct
    PRIVATE gtest gmock gmock_main gtest_ct)

# Add include directories for gtest if needed (in case gtest isn't in the standard path)
target_include_directories(test_gtest_ct
    PRIVATE ${gtest_SOURCE_DIR}/include)
