add_executable(test_gtest_ct
    passing_tests.cpp)

target_link_libraries(test_gtest_ct PRIVATE gtest gmock gmock_main gtest_ct)