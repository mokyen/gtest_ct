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