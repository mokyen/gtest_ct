add_library(gtest_ct INTERFACE)
target_include_directories(gtest_ct INTERFACE .)

target_link_libraries(gtest_ct PRIVATE gtest gmock)
