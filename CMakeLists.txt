cmake_minimum_required(VERSION 3.13)

# Define the project name and version
project(gtest_ct VERSION 1.0.0)

# Option to build tests, default is OFF
option(gtest_ct_build_tests "Build gtest_ct's self-tests." OFF)

# Make sure to include the directory with your headers
add_library(gtest_ct INTERFACE)
target_include_directories(gtest_ct INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add subdirectory for the tests if enabled
if (gtest_ct_build_tests)
    add_subdirectory(test)
endif()

# USAGE
# In the target that uses the library:
# target_link_libraries(dependee
#    PUBLIC/INTERFACE/PRIVATE # pick one
#    gtest_ct)
#
# And include the header like this:
# #include <project/folder1/file.hpp>
