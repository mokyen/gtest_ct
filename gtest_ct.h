#include "gtest/gtest.h"

//=================================================
// C++ VERSION REQUIREMENTS
//=================================================
#if __cplusplus < 201103
  #error Please compile for C++11 or higher
#elif __cplusplus < 201703
  #error Pre-C++17 is not yet supported.
#endif

//=================================================
// CT RESULT STORAGE
//=================================================
struct result {

#if __cplusplus < 202002
constexpr result(bool assertion, std::string_view msg) : didTestPass{assertion}, failureMsg{msg}
{}
#else
consteval result(bool assertion, std::string_view msg) : didTestPass{assertion}, failureMsg{msg}
{}
#endif

const bool didTestPass;
const std::string_view failureMsg;
};

//=================================================
// STOP ON COMPILE-TIME FAILURE
//=================================================
// Define this to fail the build when a CT failure occurs
// #define STOP_ON_CT_FAIL

#ifdef STOP_ON_CT_FAIL
#define ASSERT_ON_BUILD(X) static_assert(X, "gtest_ct failure: "#X);
#else
#define ASSERT_ON_BUILD(X) do { } while(0);
#endif

//=================================================
// EXPECTS
//=================================================
#define CT_EXPECT_TRUE(X) \
do { \
    ASSERT_ON_BUILD(X) \
    constexpr result x{X, #X};\
    EXPECT_TRUE(x.didTestPass) << "gtest_ct failure: " << x.failureMsg;\
} while (0)

#define CT_EXPECT_FALSE(X) \
do { \
    CT_EXPECT_TRUE(!(X)); \
} while (0)

#define CT_EXPECT_EQ(X, Y) \
do { \
    CT_EXPECT_TRUE(X == Y);\
} while (0)

#define CT_EXPECT_NE(X, Y) \
do { \
    CT_EXPECT_TRUE(X == Y);\
} while (0)

//=================================================
// ASSERTS
//=================================================
#define CT_ASSERT_TRUE(X) \
do { \
    ASSERT_ON_BUILD(X) \
    constexpr result x{X, #X};\
    ASSERT_TRUE(x.didTestPass) << "gtest_ct failure: " << x.failureMsg;\
} while (0)

#define CT_ASSERT_FALSE(X) \
do { \
    ASSERT_ON_BUILD(!(X)); \
} while (0)

#define CT_ASSERT_EQ(X, Y) \
do { \
    CT_ASSERT_TRUE(X == Y);\
} while (0)

#define CT_ASSERT_NE(X, Y) \
do { \
    CT_ASSERT_FALSE(X == Y);\
} while (0)


//TODO (plus assert versions)
//CT_EXPECT_LT
//CT_EXPECT_LE
//CT_EXPECT_GT
//CT_EXPECT_GE
//CT_EXPECT_STREQ?
//CT_EXPECT_STRNE?
//CT_EXPECT_STRCASEEQ?
//CT_EXPECT_STRCASENE?
//CT_EXPECT_FLOAT_EQ
//CT_EXPECT_DOUBLE_EQ
//CT_EXPECT_NEAR


//=================================================
// Testing usage
// TODO Break this out into separate file and more tests
//=================================================

constexpr int foo (int x) { return x; }


TEST(setup_test_case, testWillPass)
{
    constexpr  auto a{foo (5)};
    CT_EXPECT_TRUE(a == 5);
    CT_EXPECT_TRUE(a != 6);
    CT_EXPECT_EQ(a, 5);

    // CT_ASSERT_FALSE(a == 5);
    CT_ASSERT_NE(a, 7);

    const int a1{7};
    // CT_ASSERT_EQ(4, 42);
    CT_EXPECT_FALSE(4 == 4);

    int* a2;

    EXPECT_EQ(*a2, 7);
}