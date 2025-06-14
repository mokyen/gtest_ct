cmake_minimum_required(VERSION 3.13)

# Define the project name and version
project(gtest_ct VERSION 1.0.0)

# Include utilities
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(utilities)

# Option to build tests, default is OFF
option(gtest_ct_build_tests "Build gtest_ct's self-tests." OFF)

# Add the header-only library from the include directory
add_subdirectory(include)

# Add subdirectory for the tests if enabled
if (gtest_ct_build_tests)
    # Enable testing
    enable_testing()
    add_subdirectory(test)
endif()
