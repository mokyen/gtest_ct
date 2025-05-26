#!/bin/bash
# Create all the compile-fail test files

cd test/compilation_fail_tests

# Template for test files
create_test_file() {
    local assertion_type="$1"
    local filename="ct_assert_${assertion_type}_fail.cpp"
    local assertion="$2"
    echo "#define STOP_ON_CT_FAIL" >> "${filename}"
    echo "#include \"gtest_ct.h\"" >> "${filename}"
    echo "" >> "${filename}"
    echo "TEST(CompileTimeTests, ExpectFailTest_${assertion_type}) {" >> "${filename}"
    echo "    ${assertion}" >> "${filename}"
    echo "}" >> "${filename}"
    
    echo "Created ${filename}"
}

# Create each test file
create_test_file "true" "CT_ASSERT_TRUE(false);"
create_test_file "false" "CT_ASSERT_FALSE(true);"
create_test_file "eq" "CT_ASSERT_EQ(1, 2);"
create_test_file "ne" "CT_ASSERT_NE(1, 1);"
create_test_file "lt" "CT_ASSERT_LT(2, 1);"
create_test_file "le" "CT_ASSERT_LE(2, 1);"
create_test_file "gt" "CT_ASSERT_GT(1, 2);"
create_test_file "ge" "CT_ASSERT_GE(1, 2);"
create_test_file "streq" "CT_ASSERT_STREQ(\"foo\", \"bar\");"
create_test_file "strne" "CT_ASSERT_STRNE(\"foo\", \"foo\");"
create_test_file "strcaseeq" "CT_ASSERT_STRCASEEQ(\"foo\", \"FOO1\");"
create_test_file "strcasene" "CT_ASSERT_STRCASENE(\"foo\", \"FOO\");"
create_test_file "float_eq" "CT_ASSERT_FLOAT_EQ(1.0f, 2.0f);"
create_test_file "double_eq" "CT_ASSERT_DOUBLE_EQ(1.0, 2.0);"
create_test_file "near" "CT_ASSERT_NEAR(1.0, 2.0, 0.1);"