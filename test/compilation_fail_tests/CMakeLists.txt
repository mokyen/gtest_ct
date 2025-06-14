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