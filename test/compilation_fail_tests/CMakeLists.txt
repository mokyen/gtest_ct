cmake_minimum_required(VERSION 3.16)
project(CompileFailTests NONE)

# Set default C++ standard if not already set externally
if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Allow manual override with cmake -Dcompile_fail_force_std=20
set(compile_fail_force_std "${CMAKE_CXX_STANDARD}" CACHE STRING "C++ standard to test compilation failures with")

# Create a function to define a compile-failure test
function(add_compile_fail_test TEST_NAME SOURCE_FILE)
    set(SRC_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE}")

    add_test(NAME "${TEST_NAME}"
        COMMAND
            ${CMAKE_CXX_COMPILER}
            -std=c++${compile_fail_force_std}
            -I${CMAKE_SOURCE_DIR}/include
            -I$ENV{HOME}/gtest_install/include
            -c "${SRC_PATH}"
            -o "${CMAKE_BINARY_DIR}/${TEST_NAME}.o"
    )
    set_tests_properties("${TEST_NAME}" PROPERTIES
        WILL_FAIL TRUE
        LABELS "compilefail"
    )
endfunction()

# One test per CT_ASSERT macro
add_compile_fail_test(ct_assert_true_fail ct_assert_true_fail.cpp)
add_compile_fail_test(ct_assert_false_fail ct_assert_false_fail.cpp)
add_compile_fail_test(ct_assert_eq_fail ct_assert_eq_fail.cpp)
add_compile_fail_test(ct_assert_ne_fail ct_assert_ne_fail.cpp)
add_compile_fail_test(ct_assert_lt_fail ct_assert_lt_fail.cpp)
add_compile_fail_test(ct_assert_le_fail ct_assert_le_fail.cpp)
add_compile_fail_test(ct_assert_gt_fail ct_assert_gt_fail.cpp)
add_compile_fail_test(ct_assert_ge_fail ct_assert_ge_fail.cpp)
add_compile_fail_test(ct_assert_streq_fail ct_assert_streq_fail.cpp)
add_compile_fail_test(ct_assert_strne_fail ct_assert_strne_fail.cpp)
add_compile_fail_test(ct_assert_strcaseeq_fail ct_assert_strcaseeq_fail.cpp)
add_compile_fail_test(ct_assert_strcasene_fail ct_assert_strcasene_fail.cpp)
add_compile_fail_test(ct_assert_float_eq_fail ct_assert_float_eq_fail.cpp)
add_compile_fail_test(ct_assert_double_eq_fail ct_assert_double_eq_fail.cpp)
add_compile_fail_test(ct_assert_near_fail ct_assert_near_fail.cpp)

# Add a custom target to run all compile-fail tests
add_custom_target(run_compile_fail_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -L compilefail
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running all compile-fail tests"
)