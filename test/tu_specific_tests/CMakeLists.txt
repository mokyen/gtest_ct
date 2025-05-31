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

# Test that continues compilation despite failures
add_executable(ct_continue_test ct_continue_test.cpp)
target_include_directories(ct_continue_test  PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)
target_link_libraries(ct_continue_test PRIVATE 
    GTest::GTest 
    GTest::Main
)
add_test(
    NAME ct_continue_test
    COMMAND ct_continue_test
)

# Add to existing compilation fail tests
add_compile_fail_test(ct_conflicting_flags_fail ct_conflicting_flags_fail.cpp)
