#include "gtest_ct.h"

// Helper Functions and Structures
constexpr int foo(int x) { return x; }

class TestStruct {
 public:
  constexpr TestStruct(int c, int d) : a{c}, b{d} {}
  constexpr bool operator==(const TestStruct& rhs) const {
    return (this->a == rhs.a) && (this->b == rhs.b);
  }
  constexpr bool operator<(const TestStruct& rhs) const {
    return (this->a < rhs.a) || (this->a == rhs.a && this->b < rhs.b);
  }

 private:
  int a, b;
};

// EXPECT Tests
TEST(CT_EXPECT_TESTS, BASICS) {
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

TEST(CT_EXPECT_TESTS, RELATIONAL_OPERATORS) {
  constexpr int a = 5;
  constexpr int b = 10;

  CT_EXPECT_LT(a, b);
  CT_EXPECT_LE(a, b);
  CT_EXPECT_LE(a, a);

  CT_EXPECT_GT(b, a);
  CT_EXPECT_GE(b, a);
  CT_EXPECT_GE(b, b);
}

TEST(CT_EXPECT_TESTS, FLOATING_POINT_COMPARISONS) {
  constexpr float f1 = 0.1f;
  constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();

  CT_EXPECT_FLOAT_EQ(f1, f2);
  CT_EXPECT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f2));
  CT_EXPECT_NEAR(1.0, 1.001, 0.01);
}

TEST(CT_EXPECT_TESTS, C_STRING_COMPARISONS) {
  constexpr const char* str1 = "hello";
  constexpr const char* str2 = "hello";
  constexpr const char* str3 = "world";
  constexpr const char* str4 = "HELLO";

  CT_EXPECT_STREQ(str1, str2);
  CT_EXPECT_STRNE(str1, str3);

  CT_EXPECT_STRCASEEQ(str1, str4);
  CT_EXPECT_STRCASENE(str1, str3);
}

TEST(CT_EXPECT_TESTS, CT_EXPECT_CONTINUES) {
  CT_EXPECT_TRUE(true);
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_TRUE(false); }, "");
}

TEST(CT_EXPECT_TESTS, COMBINED_CT_RT_EXPECT) {
  CT_EXPECT_TRUE(true);
  EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); }, "");
}

// ASSERT Tests
TEST(CT_ASSERT_TESTS, BASICS) {
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

TEST(CT_ASSERT_TESTS, RELATIONAL_OPERATORS) {
  constexpr int a = 5;
  constexpr int b = 10;

  CT_ASSERT_LT(a, b);
  CT_ASSERT_LE(a, b);
  CT_ASSERT_LE(a, a);

  CT_ASSERT_GT(b, a);
  CT_ASSERT_GE(b, a);
  CT_ASSERT_GE(b, b);
}

TEST(CT_ASSERT_TESTS, FLOATING_POINT_COMPARISONS) {
  constexpr float f1 = 0.1f;
  // constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();
  constexpr float epsilon = std::numeric_limits<float>::epsilon();
constexpr float f2 = f1 + epsilon;

// Add these static_asserts and see which one fails compilation with Clang
static_assert(f2 > f1, "f2 should be greater than f1"); // Basic check
static_assert(f2 - f1 == epsilon, "f2 - f1 should equal epsilon"); // Crucial check
static_assert(std::abs(f1 - f2) == epsilon, "abs(f1 - f2) should equal epsilon"); // Check abs
static_assert(std::abs(f1 + f2) > 0.0f, "abs(f1+f2) should be positive"); // Check the other term
static_assert(std::numeric_limits<float>::epsilon() > 0.0f, "epsilon should be positive"); // Check epsilon value itself

// Then check parts of the almost_equal calculation
// static_assert(std::abs(f1 - f2) <= std::numeric_limits<float>::epsilon() * std::abs(f1 + f2) * 1024); // This is the original check, should fail
// static_assert(std::numeric_limits<float>::epsilon() <= std::numeric_limits<float>::epsilon() * std::abs(f1 + f2) * 1024); // Simplified check, should fail

  CT_ASSERT_FLOAT_EQ(f1, f2);
  CT_ASSERT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f2));
  CT_ASSERT_NEAR(1.0, 1.001, 0.01);
}

// Define f1, f2, almost_equal as in your gtest_ct.h and passing_tests.cpp
constexpr float f1 = 0.1f;
constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();
constexpr int test_ulp = 1024;

// This line mimics the problematic part of the macro
constexpr result test_res{almost_equal<float>(f1, f2, test_ulp), "almost_equal<float>(f1, f2, 1024)"};

TEST(FloatingPointDebug, IsolatedConstexprResult) {
  // Check the result of the compile-time evaluation
  EXPECT_TRUE(test_res.didTestPass); // This is what's failing in your original tests
}

TEST(FloatingPointDebug, IsolatedConstexprResultInTest) {
  constexpr float f1 = 0.1f;
  constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();
  constexpr int test_ulp = 1024;

  // Direct initialization of constexpr result within a TEST macro
  constexpr result test_res{almost_equal<float>(f1, f2, test_ulp), "almost_equal<float>(f1, f2, 1024)"};

  // Check the result using standard Google Test EXPECT
  EXPECT_TRUE(test_res.didTestPass);
  if (!test_res.didTestPass) {
      // You can print the failure message here if needed, though EXPECT_TRUE does it
      // std::cerr << "Failure: " << test_res.failureMsg.getString() << std::endl;
  }
}

TEST(FloatingPointDebug, ConstexprResultAndExpectDirect) {
  constexpr float f1 = 0.1f;
  constexpr float f2 = f1 + std::numeric_limits<float>::epsilon();
  constexpr int test_ulp = 1024;
  constexpr bool condition = almost_equal<float>(f1, f2, test_ulp); // Evaluate the condition separately

  // Mimic the problematic part of the macro, but without the do/while(0)
  constexpr result x{condition, "almost_equal<float>(f1, f2, 1024)"};

  // The runtime assertion part of the macro
  EXPECT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG;
}

TEST(CT_ASSERT_TESTS, C_STRING_COMPARISONS) {
  constexpr const char* str1 = "hello";
  constexpr const char* str2 = "hello";
  constexpr const char* str3 = "world";
  constexpr const char* str4 = "HELLO";

  CT_ASSERT_STREQ(str1, str2);
  CT_ASSERT_STRNE(str1, str3);

  CT_ASSERT_STRCASEEQ(str1, str4);
  CT_ASSERT_STRCASENE(str1, str3);
}

TEST(CT_ASSERT_TESTS, CT_ASSERT_DOESNT_CONTINUE) {
  EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
  EXPECT_TRUE(false) << "This shouldn't be evaluated";
}

TEST(CT_ASSERT_TESTS, COMBINED_CT_RT_EXPECT) {
  CT_ASSERT_TRUE(true);
  EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); }, "");
}

// EXPECT Failure Tests
TEST(CT_EXPECT_FAILURE_TESTS, BASICS) {
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

TEST(CT_EXPECT_FAILURE_TESTS, RELATIONAL_OPERATORS) {
  constexpr int a = 5;
  constexpr int b = 10;

  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_LT(b, a); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_LE(b, a - 1); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_GT(a, b); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_GE(a, b + 1); }, "");
}

TEST(CT_EXPECT_FAILURE_TESTS, FLOATING_POINT_COMPARISONS) {
  constexpr float f1 = 0.1f;
  constexpr float f2 = f1 + 10 * std::numeric_limits<float>::epsilon();

  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_FLOAT_EQ(f1, f2); }, "");
  EXPECT_NONFATAL_FAILURE(
      { CT_EXPECT_DOUBLE_EQ(static_cast<double>(f1), static_cast<double>(f1 * 2)); },
      "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NEAR(1.0, 1.1, 0.01); }, "");
}

TEST(CT_EXPECT_FAILURE_TESTS, C_STRING_COMPARISONS) {
  constexpr const char* str1 = "hello";
  constexpr const char* str2 = "world";
  constexpr const char* str3 = "HELLO";

  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STREQ(str1, str2); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRNE(str1, str1); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRCASEEQ(str1, str2); }, "");
  EXPECT_NONFATAL_FAILURE({ CT_EXPECT_STRCASENE(str1, str3); }, "");
}

// ASSERT Failure Tests
TEST(CT_ASSERT_FAILURE_TESTS, BASICS2) {
  EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
  EXPECT_FATAL_FAILURE({ CT_ASSERT_FALSE(true); }, "");
  EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(1, 2); }, "");
  EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(1, 1); }, "");

  constexpr TestStruct A{1, 2};
  constexpr TestStruct B{1, 2};
  constexpr TestStruct C{2, 2};

  // TODO(mokyen): not working yet
  // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, A); }, "");
  // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, B); }, "");
  // EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(A, C); }, "");
}