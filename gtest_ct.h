#include "gtest/gtest.h"

//TODO add usage information
//https://godbolt.org/z/xhnY87rcM

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
// EXPECTS
//=================================================
#define CT_EXPECT_TRUE(X) \
do { \
    ASSERT_ON_BUILD(X) \
    constexpr result x{X, #X};\
    EXPECT_TRUE(x.didTestPass) << "gtest_ct failure: " << x.failureMsg.getString();\
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
    ASSERT_TRUE(x.didTestPass) << "gtest_ct failure: " << x.failureMsg.getString();\
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

// constexpr str_const bar () {
//     constexpr str_const test("Hi Mom!");
//     static_assert(test.size() == 7);
//     static_assert(test[6] == '!');
//     return test;
// }


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

    // constexpr auto a3{bar()};
    constexpr str_const a3{"Hi Mom!"};
    EXPECT_STREQ("ABC", a3.getString()) << a3.getString();
}

/*
TODO Tests to write
NO FAIL COMPILATION ON CT FAILS
* basic CT expect_true/assert true passes
* basic CT expect_true false causes fail
* basic CT expect_false/assert false passes
* basic CT expect_false true causes fail

* basic CT expect_eq/assert_eq true equals true passes
* basic CT expect_eq/assert_eq false equals false passes
* basic CT expect_eq/assert_eq true equals false fails
* basic CT expect_eq/assert_eq int equals same int passes
* basic CT expect_eq/assert_eq int equals different int fails
* basic CT expect_eq/assert_eq objects

* inverse of last grouping with _ne

* assert test(s) showing that results stop after assert fail
* expect test(s) showing that results continue after test fail

* test(s) showing interweaving CT and RT tests


FAIL COMPILATION ON CT FAILS
* show that expect/assert tests fail compilation


*/