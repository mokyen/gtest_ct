#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include <algorithm>

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
