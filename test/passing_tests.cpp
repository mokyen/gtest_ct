#include "gtest_ct.h" 

//=================================================
// Helper Functions and Structures
//=================================================

constexpr int foo(int x) { return x; }

class TestStruct
{
public:
    constexpr TestStruct(int c, int d) : a{c}, b{d} {}
    constexpr bool operator==(const TestStruct& rhs) const { return (this->a == rhs.a) && (this->b == rhs.b); }
    constexpr bool operator<(const TestStruct& rhs) const { return (this->a < rhs.a) || (this->a == rhs.a && this->b < rhs.b); }

private:
    int a, b;
};

//=================================================
// EXPECT Tests
//=================================================

TEST(CT_EXPECT_TESTS, BASICS)
{
    constexpr bool t{true};
    CT_EXPECT_TRUE(t);
    constexpr bool f{false};
    CT_EXPECT_FALSE(f);

    CT_EXPECT_EQ(true, true);
    CT_EXPECT_NE(true, false);

    CT_EXPECT_EQ(1, 1);
    CT_EXPECT_NE(1, 2);

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    CT_EXPECT_EQ(A, A);
    CT_EXPECT_EQ(A, B);
    CT_EXPECT_NE(A, C);
}

TEST(CT_EXPECT_TESTS, RELATIONAL_OPERATORS)
{
    constexpr int a = 5;
    constexpr int b = 10;

    CT_EXPECT_LT(a, b);
    CT_EXPECT_LE(a, b);
    CT_EXPECT_LE(a, a);

    CT_EXPECT_GT(b, a);
    CT_EXPECT_GE(b, a);
    CT_EXPECT_GE(b, b);
}

TEST(CT_EXPECT_TESTS, FLOATING_POINT_COMPARISONS)
{
    constexpr float f1 = 0.1f;
    constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();

    CT_EXPECT_FLOAT_EQ(f1, f2);
    CT_EXPECT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f2));
    CT_EXPECT_NEAR(1.0, 1.001, 0.01);
}

TEST(CT_EXPECT_TESTS, C_STRING_COMPARISONS)
{
    constexpr const char* str1 = "hello";
    constexpr const char* str2 = "hello";
    constexpr const char* str3 = "world";
    constexpr const char* str4 = "HELLO";

    CT_EXPECT_STREQ(str1, str2);
    CT_EXPECT_STRNE(str1, str3);

    CT_EXPECT_STRCASEEQ(str1, str4);
    CT_EXPECT_STRCASENE(str1, str3);
}

TEST(CT_EXPECT_TESTS, CT_EXPECT_CONTINUES)
{
    CT_EXPECT_TRUE(true);
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_TRUE(false); }, "");
}

TEST(CT_EXPECT_TESTS, COMBINED_CT_RT_EXPECT)
{
    CT_EXPECT_TRUE(true);
    EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); }, "");
}

//=================================================
// ASSERT Tests
//=================================================

TEST(CT_ASSERT_TESTS, BASICS)
{
    constexpr bool t{true};
    CT_ASSERT_TRUE(t);
    constexpr bool f{false};
    CT_ASSERT_FALSE(f);

    CT_ASSERT_EQ(true, true);
    CT_ASSERT_NE(true, false);

    CT_ASSERT_EQ(1, 1);
    CT_ASSERT_NE(1, 2);

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    CT_ASSERT_EQ(A, A);
    CT_ASSERT_EQ(A, B);
    CT_ASSERT_NE(A, C);
}

TEST(CT_ASSERT_TESTS, RELATIONAL_OPERATORS)
{
    constexpr int a = 5;
    constexpr int b = 10;

    CT_ASSERT_LT(a, b);
    CT_ASSERT_LE(a, b);
    CT_ASSERT_LE(a, a);

    CT_ASSERT_GT(b, a);
    CT_ASSERT_GE(b, a);
    CT_ASSERT_GE(b, b);
}

TEST(CT_ASSERT_TESTS, FLOATING_POINT_COMPARISONS)
{
    constexpr float f1 = 0.1f;
    constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();

    CT_ASSERT_FLOAT_EQ(f1, f2);
    CT_ASSERT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f2));
    CT_ASSERT_NEAR(1.0, 1.001, 0.01);
}

TEST(CT_ASSERT_TESTS, C_STRING_COMPARISONS)
{
    constexpr const char* str1 = "hello";
    constexpr const char* str2 = "hello";
    constexpr const char* str3 = "world";
    constexpr const char* str4 = "HELLO";

    CT_ASSERT_STREQ(str1, str2);
    CT_ASSERT_STRNE(str1, str3);

    CT_ASSERT_STRCASEEQ(str1, str4);
    CT_ASSERT_STRCASENE(str1, str3);
}

TEST(CT_ASSERT_TESTS, CT_ASSERT_DOESNT_CONTINUE)
{
    EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
    EXPECT_TRUE(false) << "This shouldn't be evaluated";
}

TEST(CT_ASSERT_TESTS, COMBINED_CT_RT_EXPECT)
{
    CT_ASSERT_TRUE(true);
    EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); }, "");
}

//=================================================
// EXPECT Failure Tests
//=================================================

TEST(CT_EXPECT_FAILURE_TESTS, BASICS)
{
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_TRUE(false); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_FALSE(true); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_EQ(1, 2); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(1, 1); }, "");

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(A, A); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(A, B); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_EQ(A, C); }, "");
}

TEST(CT_EXPECT_FAILURE_TESTS, RELATIONAL_OPERATORS)
{
    constexpr int a = 5;
    constexpr int b = 10;

    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_LT(b, a); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_LE(b, a - 1); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_GT(a, b); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_GE(a, b + 1); }, "");
}

TEST(CT_EXPECT_FAILURE_TESTS, FLOATING_POINT_COMPARISONS)
{
    constexpr float f1 = 0.1f;
    constexpr float f2 = f1 + 10 * std::numeric_limits<float>::epsilon();

    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_FLOAT_EQ(f1, f2); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f1 * 2)); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NEAR(1.0, 1.1, 0.01); }, "");
}

TEST(CT_EXPECT_FAILURE_TESTS, C_STRING_COMPARISONS)
{
    constexpr const char* str1 = "hello";
    constexpr const char* str2 = "world";
    constexpr const char* str3 = "HELLO";

    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STREQ(str1, str2); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRNE(str1, str1); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRCASEEQ(str1, str2); }, "");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRCASENE(str1, str3); }, "");
}

//=================================================
// ASSERT Failure Tests
//=================================================

TEST(CT_ASSERT_FAILURE_TESTS, BASICS2)
{
    EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_FALSE(true); }, "");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(1, 2); }, "");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(1, 1); }, "");

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    //TODO not working yet
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, A); }, "");
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, B); }, "");
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(A, C); }, "");
}
