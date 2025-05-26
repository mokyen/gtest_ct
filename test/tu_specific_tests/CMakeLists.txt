project(TUSpecificTests)

# Use the same C++ standard as other tests
set(compile_fail_force_std "${CMAKE_CXX_STANDARD}" CACHE STRING "C++ standard to test compilation failures with")

# Find GTest package
find_package(GTest REQUIRED)

# Add compile-fail test
add_compile_fail_test(tu_specific_fail_test tu_specific_fail.cpp)

# Add runtime test as a regular executable
add_executable(tu_specific_runtime_test tu_specific_runtime.cpp)
target_include_directories(tu_specific_runtime_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(tu_specific_runtime_test PRIVATE 
    GTest::GTest 
    GTest::Main
)

# Register the runtime test with CTest
add_test(
    NAME tu_specific_runtime_test 
    COMMAND tu_specific_runtime_test
)

# Set runtime test properties - we expect this test to fail
set_tests_properties(tu_specific_runtime_test 
    PROPERTIES
    WILL_FAIL FALSE
    LABELS "runtime"
)