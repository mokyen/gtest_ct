#include "gtest/gtest.h" 
#include "gtest/gtest-spi.h"

#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstring>
#include <limits>


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
    constexpr result(bool assertion, str_const msg) : didTestPass{assertion}, failureMsg{msg} {}
#else
    consteval result(bool assertion, str_const msg) : didTestPass{assertion}, failureMsg{msg} {}
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
// Utility Function: ULP-based Floating-Point Comparison
//=================================================
template<typename T>
constexpr bool almost_equal(T x, T y, int ulp = 4) {
    static_assert(std::is_floating_point<T>::value, "almost_equal is only for floating-point types.");
    return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
        || std::abs(x - y) < std::numeric_limits<T>::min();
}

//=================================================
// Utility Function: Case-Insensitive String Comparison
//=================================================
constexpr bool strcase_equal(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (std::tolower(*str1) != std::tolower(*str2)) {
            return false;
        }
        ++str1;
        ++str2;
    }
    return *str1 == *str2;
}

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

#define CT_EXPECT_LT(X, Y) \
do { \
    CT_EXPECT_TRUE((X) < (Y)); \
} while (0)

#define CT_EXPECT_LE(X, Y) \
do { \
    CT_EXPECT_TRUE((X) <= (Y)); \
} while (0)

#define CT_EXPECT_GT(X, Y) \
do { \
    CT_EXPECT_TRUE((X) > (Y)); \
} while (0)

#define CT_EXPECT_GE(X, Y) \
do { \
    CT_EXPECT_TRUE((X) >= (Y)); \
} while (0)

#define CT_EXPECT_STREQ(X, Y) \
do { \
    CT_EXPECT_TRUE(std::strcmp(X, Y) == 0); \
} while (0)

#define CT_EXPECT_STRNE(X, Y) \
do { \
    CT_EXPECT_FALSE(std::strcmp(X, Y) == 0); \
} while (0)

#define CT_EXPECT_STRCASEEQ(X, Y) \
do { \
    CT_EXPECT_TRUE(strcase_equal(X, Y)); \
} while (0)

#define CT_EXPECT_STRCASENE(X, Y) \
do { \
    CT_EXPECT_FALSE(strcase_equal(X, Y)); \
} while (0)

#define CT_EXPECT_FLOAT_EQ(X, Y) \
do { \
    CT_EXPECT_TRUE(almost_equal<float>(X, Y)); \
} while (0)

#define CT_EXPECT_DOUBLE_EQ(X, Y) \
do { \
    CT_EXPECT_TRUE(almost_equal<double>(X, Y)); \
} while (0)

#define CT_EXPECT_NEAR(X, Y, abs_error) \
do { \
    CT_EXPECT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
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

#define CT_ASSERT_LT(X, Y) \
do { \
    CT_ASSERT_TRUE((X) < (Y)); \
} while (0)

#define CT_ASSERT_LE(X, Y) \
do { \
    CT_ASSERT_TRUE((X) <= (Y)); \
} while (0)

#define CT_ASSERT_GT(X, Y) \
do { \
    CT_ASSERT_TRUE((X) > (Y)); \
} while (0)

#define CT_ASSERT_GE(X, Y) \
do { \
    CT_ASSERT_TRUE((X) >= (Y)); \
} while (0)

#define CT_ASSERT_STREQ(X, Y) \
do { \
    CT_ASSERT_TRUE(std::strcmp(X, Y) == 0); \
} while (0)

#define CT_ASSERT_STRNE(X, Y) \
do { \
    CT_ASSERT_FALSE(std::strcmp(X, Y) == 0); \
} while (0)

#define CT_ASSERT_STRCASEEQ(X, Y) \
do { \
    CT_ASSERT_TRUE(strcase_equal(X, Y)); \
} while (0)

#define CT_ASSERT_STRCASENE(X, Y) \
do { \
    CT_ASSERT_FALSE(strcase_equal(X, Y)); \
} while (0)

#define CT_ASSERT_FLOAT_EQ(X, Y) \
do { \
    CT_ASSERT_TRUE(almost_equal<float>(X, Y)); \
} while (0)

#define CT_ASSERT_DOUBLE_EQ(X, Y) \
do { \
    CT_ASSERT_TRUE(almost_equal<double>(X, Y)); \
} while (0)

#define CT_ASSERT_NEAR(X, Y, abs_error) \
do { \
    CT_ASSERT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
} while (0)

