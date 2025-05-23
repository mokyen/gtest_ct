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
            -c "${SRC_PATH}"
            -o "${CMAKE_BINARY_DIR}/${TEST_NAME}.o"
    )
    set_tests_properties("${TEST_NAME}" PROPERTIES WILL_FAIL TRUE)
endfunction()

# List of compile-failure tests
add_compile_fail_test(fail_on_ct_flag
    test_fail_on_ct_flag.cpp 
)
