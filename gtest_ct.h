#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"

//TODO add usage information
//https://godbolt.org/z/fWzWr3qTE

//=================================================
// C++ VERSION REQUIREMENTS
//=================================================
#if __cplusplus < 201103L
  #error Please compile for C++11 or higher
#endif

//=================================================
// C++11 constexpr string
// Adapted from Scott Schurr, "New Tools for Class and
// Library Authors", C++Now 2012
//=================================================
class str_const { // constexpr string
private:
    const char* const p_;
    const std::size_t sz_;
public:
    template<std::size_t N>
    constexpr str_const(const char(&a)[N]) : // ctor
    p_(a), sz_(N-1) {}

    constexpr const char* const getString() const {
        return p_;
    }
};

//=================================================
// CT RESULT STORAGE
//=================================================
struct result {

#if __cplusplus < 202002
constexpr result(bool assertion, str_const msg) : didTestPass{assertion}, failureMsg{msg}
{}
#else
consteval result(bool assertion, str_const msg) : didTestPass{assertion}, failureMsg{msg}
{}
#endif

const bool didTestPass;
str_const failureMsg;
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
// ASSERTIONS COMMON
//=================================================
#define STREAM_FAILURE_MSG "gtest_ct failure: " << x.failureMsg.getString()

//=================================================
// EXPECTS
//=================================================
#define CT_EXPECT_TRUE(X) \
do { \
    ASSERT_ON_BUILD(X) \
    constexpr result x{X, #X};\
    EXPECT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG;\
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
    CT_EXPECT_FALSE(X == Y);\
} while (0)

//=================================================
// ASSERTS
//=================================================
#define CT_ASSERT_TRUE(X) \
do { \
    ASSERT_ON_BUILD(X) \
    constexpr result x{X, #X};\
    ASSERT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG;\
} while (0)

#define CT_ASSERT_FALSE(X) \
do { \
    CT_ASSERT_TRUE(!(X)); \
} while (0)

#define CT_ASSERT_EQ(X, Y) \
do { \
    CT_ASSERT_TRUE(X == Y);\
} while (0)

#define CT_ASSERT_NE(X, Y) \
do { \
    CT_ASSERT_FALSE(X == Y);\
} while (0)


// //TODO (plus assert versions)
// //CT_EXPECT_LT
// //CT_EXPECT_LE
// //CT_EXPECT_GT
// //CT_EXPECT_GE
// //CT_EXPECT_STREQ?
// //CT_EXPECT_STRNE?
// //CT_EXPECT_STRCASEEQ?
// //CT_EXPECT_STRCASENE?
// //CT_EXPECT_FLOAT_EQ
// //CT_EXPECT_DOUBLE_EQ
// //CT_EXPECT_NEAR


//=================================================
// Testing usage
// TODO Break this out into separate file and more tests
//=================================================

constexpr int foo (int x) { return x; }

class TestStruct
{
public:
    constexpr TestStruct(int c, int d) : a{c}, b{d}
    {}
    constexpr bool operator==(const TestStruct& rhs) const { return (this->a == rhs.a) && (this->b == rhs.b); }

private:
    int a, b;
};

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


//TODO WIP
TEST(CT_EXPECT_FAILURE_TESTS, BASICS)
{
     EXPECT_NONFATAL_FAILURE(CT_EXPECT_TRUE(false), "fail non-fatally");
}

/*
TODO Tests to write
NO FAIL COMPILATION ON CT FAILS
X* basic CT expect_true/assert true passes
* basic CT expect_true false causes fail
X* basic CT expect_false/assert false passes
* basic CT expect_false true causes fail

X* basic CT expect_eq/assert_eq true equals true passes
X* basic CT expect_eq/assert_eq false equals false passes
* basic CT expect_eq/assert_eq true equals false fails
X* basic CT expect_eq/assert_eq int equals same int passes
* basic CT expect_eq/assert_eq int equals different int fails
X* basic CT expect_eq/assert_eq objects

X* inverse of last grouping with _ne

* assert test(s) showing that results stop after assert fail
* expect test(s) showing that results continue after test fail

* test(s) showing interweaving CT and RT tests


FAIL COMPILATION ON CT FAILS
* show that expect/assert tests fail compilation


*/