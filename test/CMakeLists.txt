# Set the C++ standard for compile-fail tests (used by utilities.cmake)
set(compile_fail_force_std 17 CACHE STRING "C++ standard to test compilation failures with")

add_subdirectory(passing_tests)
add_subdirectory(compilation_fail_tests)
add_subdirectory(tu_specific_tests)
