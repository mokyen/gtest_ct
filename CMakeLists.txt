cmake_minimum_required(VERSION 3.13)

# Define the project name and version
project(gtest_ct VERSION 1.0.0)

# Include utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utilities)

# Option to build tests, default is OFF
option(gtest_ct_build_tests "Build gtest_ct's self-tests." OFF)

# Make sure to include the directory with your headers
add_library(gtest_ct INTERFACE)
target_include_directories(gtest_ct INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add subdirectory for the tests if enabled
if (gtest_ct_build_tests)
    # Enable testing
    enable_testing()
    add_subdirectory(test)
endif()
