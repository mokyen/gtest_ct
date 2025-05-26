// System headers
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <limits>

// GTest headers
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"

// C++ VERSION REQUIREMENTS
#if __cplusplus < 201103L
#error Please compile for C++11 or higher
#endif

// Define a unique identifier for each translation unit
#ifndef GTEST_CT_TU_ENABLED
#define GTEST_CT_TU_ENABLED 0
#endif

// C++11 constexpr string
// Adapted from Scott Schurr, "New Tools for Class and
// Library Authors", C++Now 2012
class str_const {  // constexpr string
 private:
  const char* const p_;
  const std::size_t sz_;

 public:
  template <std::size_t N>
  constexpr str_const(const char (&a)[N])  // ctor
      : p_(a), sz_(N - 1) {}

  constexpr const char* const getString() const { return p_; }
};

// constexpr implementation of strcmp for C++11/14/17
constexpr int constexpr_strcmp(const char* s1, const char* s2) {
    return (*s1 == *s2)
        ? ((*s1 == '\0') ? 0 : constexpr_strcmp(s1 + 1, s2 + 1))
        : ((*s1 < *s2) ? -1 : 1);
}

// CT RESULT STORAGE
struct result {
#if __cplusplus < 202002
  constexpr result(bool assertion, str_const msg)
      : didTestPass{assertion}, failureMsg{msg} {}
#else
  consteval result(bool assertion, str_const msg)
      : didTestPass{assertion}, failureMsg{msg} {}
#endif

  const bool didTestPass;
  str_const failureMsg;
};

// STOP ON COMPILE-TIME FAILURE
// Define this to fail the build when a CT failure occurs
// Note that this is a global flag and can be overridden
// #define STOP_ON_CT_FAIL

// Macro to enable CT failures for this translation unit
#define ENABLE_CT_FAILURES() static constexpr bool GTEST_CT_TU_ENABLED = true

// Check both global flag and per-translation unit flag
#if defined(STOP_ON_CT_FAIL)
#define ASSERT_ON_BUILD(X) static_assert(X, "gtest_ct failure: " #X);
#elif defined(GTEST_CT_TU_ENABLED) && GTEST_CT_TU_ENABLED
#define ASSERT_ON_BUILD(X) static_assert(X, "gtest_ct failure: " #X);
#else
#define ASSERT_ON_BUILD(X) \
  do {                     \
  } while (0);
#endif

// ASSERTIONS COMMON
#define STREAM_FAILURE_MSG "gtest_ct failure: " << x.failureMsg.getString()

// Utility Function: ULP-based Floating-Point Comparison
template <typename T>
constexpr bool almost_equal(T x, T y, int ulp = 5) {
  static_assert(std::is_floating_point<T>::value,
                "almost_equal is only for floating-point types.");
  return std::abs(x - y) <= std::numeric_limits<T>::epsilon() *
                               std::abs(x + y) * ulp ||
         std::abs(x - y) < std::numeric_limits<T>::min();
}

// Utility Function: Char to lowercase
constexpr char char_to_lower(char c) {
  return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
}

constexpr bool strcase_equal(const char* s1, const char* s2) {
    return (char_to_lower(*s1) == char_to_lower(*s2))
        ? (*s1 == '\0'
            ? true
            : strcase_equal(s1 + 1, s2 + 1))
        : false;
}

// EXPECTS
#define CT_EXPECT_TRUE(X)                             \
  do {                                               \
    ASSERT_ON_BUILD(X)                               \
    constexpr result x{X, #X};                       \
    EXPECT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG; \
  } while (0)

#define CT_EXPECT_FALSE(X) \
  do {                     \
    CT_EXPECT_TRUE(!(X));  \
  } while (0)

#define CT_EXPECT_EQ(X, Y)    \
  do {                        \
    CT_EXPECT_TRUE(X == Y);   \
  } while (0)

#define CT_EXPECT_NE(X, Y)      \
  do {                          \
    CT_EXPECT_FALSE(X == Y);    \
  } while (0)

#define CT_EXPECT_LT(X, Y)    \
  do {                        \
    CT_EXPECT_TRUE((X) < (Y)); \
  } while (0)

#define CT_EXPECT_LE(X, Y)     \
  do {                         \
    CT_EXPECT_TRUE((X) <= (Y)); \
  } while (0)

#define CT_EXPECT_GT(X, Y)    \
  do {                        \
    CT_EXPECT_TRUE((X) > (Y)); \
  } while (0)

#define CT_EXPECT_GE(X, Y)     \
  do {                         \
    CT_EXPECT_TRUE((X) >= (Y)); \
  } while (0)

#define CT_EXPECT_STREQ(X, Y)                   \
  do {                                          \
    CT_EXPECT_TRUE(constexpr_strcmp(X, Y) == 0);     \
  } while (0)

#define CT_EXPECT_STRNE(X, Y)                   \
  do {                                          \
    CT_EXPECT_FALSE(constexpr_strcmp(X, Y) == 0);    \
  } while (0)

#define CT_EXPECT_STRCASEEQ(X, Y)           \
  do {                                      \
    CT_EXPECT_TRUE(strcase_equal(X, Y));    \
  } while (0)

#define CT_EXPECT_STRCASENE(X, Y)           \
  do {                                      \
    CT_EXPECT_FALSE(strcase_equal(X, Y));   \
  } while (0)

#define CT_EXPECT_FLOAT_EQ(X, Y)               \
  do {                                         \
    CT_EXPECT_TRUE(almost_equal<float>(X, Y)); \
  } while (0)

#define CT_EXPECT_DOUBLE_EQ(X, Y)               \
  do {                                          \
    CT_EXPECT_TRUE(almost_equal<double>(X, Y)); \
  } while (0)

#define CT_EXPECT_NEAR(X, Y, abs_error)                \
  do {                                                 \
    CT_EXPECT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
  } while (0)

// ASSERTS
#define CT_ASSERT_TRUE(X)                             \
  do {                                               \
    ASSERT_ON_BUILD(X)                               \
    constexpr result x{X, #X};                       \
    ASSERT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG; \
  } while (0)

#define CT_ASSERT_FALSE(X) \
  do {                     \
    CT_ASSERT_TRUE(!(X));  \
  } while (0)

#define CT_ASSERT_EQ(X, Y)    \
  do {                        \
    CT_ASSERT_TRUE(X == Y);   \
  } while (0)

#define CT_ASSERT_NE(X, Y)      \
  do {                          \
    CT_ASSERT_FALSE(X == Y);    \
  } while (0)

#define CT_ASSERT_LT(X, Y)     \
  do {                         \
    CT_ASSERT_TRUE((X) < (Y)); \
  } while (0)

#define CT_ASSERT_LE(X, Y)      \
  do {                          \
    CT_ASSERT_TRUE((X) <= (Y)); \
  } while (0)

#define CT_ASSERT_GT(X, Y)     \
  do {                         \
    CT_ASSERT_TRUE((X) > (Y)); \
  } while (0)

#define CT_ASSERT_GE(X, Y)      \
  do {                          \
    CT_ASSERT_TRUE((X) >= (Y)); \
  } while (0)

#define CT_ASSERT_STREQ(X, Y)                   \
  do {                                          \
    CT_ASSERT_TRUE(constexpr_strcmp(X, Y) == 0);     \
  } while (0)

#define CT_ASSERT_STRNE(X, Y)                   \
  do {                                          \
    CT_ASSERT_FALSE(constexpr_strcmp(X, Y) == 0);    \
  } while (0)

#define CT_ASSERT_STRCASEEQ(X, Y)           \
  do {                                      \
    CT_ASSERT_TRUE(strcase_equal(X, Y));    \
  } while (0)

#define CT_ASSERT_STRCASENE(X, Y)           \
  do {                                      \
    CT_ASSERT_FALSE(strcase_equal(X, Y));   \
  } while (0)

#define CT_ASSERT_FLOAT_EQ(X, Y)               \
  do {                                         \
    CT_ASSERT_TRUE(almost_equal<float>(X, Y)); \
  } while (0)

#define CT_ASSERT_DOUBLE_EQ(X, Y)               \
  do {                                          \
    CT_ASSERT_TRUE(almost_equal<double>(X, Y)); \
  } while (0)

#define CT_ASSERT_NEAR(X, Y, abs_error)                \
  do {                                                 \
    CT_ASSERT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
  } while (0)

#define CT_ASSERT_TRUE_SIMPLIFIED_FOR_TEST(X) \
  do {                                        \
    ASSERT_TRUE(X) << "Simplified CT_ASSERT_TRUE failure: " #X; \
  } while (0)