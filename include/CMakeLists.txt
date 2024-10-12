add_library(gtest_ct INTERFACE)

# Make sure the include directory is properly set
target_include_directories(gtest_ct INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Since this is a header-only library, you should not link any libraries with PRIVATE.
# You may want to use INTERFACE if the consumer of gtest_ct requires gtest and gmock.
target_link_libraries(gtest_ct INTERFACE gtest gmock)
