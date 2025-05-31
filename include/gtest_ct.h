#ifndef GTEST_CT_H_
#define GTEST_CT_H_

// =============================================================================
// Includes
// =============================================================================

// Standard headers
#include <cctype>
#include <cmath>
#include <cstring>
#include <limits>
#include <type_traits>

// GoogleTest headers
#include "gtest/gtest-spi.h"
#include "gtest/gtest.h"

// C++ Version Check
#if __cplusplus < 201103L
#error Please compile for C++11 or higher
#endif

// =============================================================================
// Global Flags & Compile-Time Configuration
// =============================================================================

// Define a unique identifier for each translation unit if not provided.
#ifndef GTEST_CT_TU_ENABLED
#define GTEST_CT_TU_ENABLED 0
#endif

// Uncomment one of the following in your build if you wish to change the behavior:
//#define STOP_ON_CT_FAIL       // Fail the build on a CT failure.
//#define CONTINUE_ON_CT_FAIL   // Continue the build even when a CT failure occurs.

#if defined(STOP_ON_CT_FAIL) && defined(CONTINUE_ON_CT_FAIL)
#error Cannot define both STOP_ON_CT_FAIL and CONTINUE_ON_CT_FAIL
#endif

// Macro to enable compile-time failures for this translation unit.
#ifdef CONTINUE_ON_CT_FAIL
  // When continuing on CT failures, don't enable compile-time failure behavior.
  #define ENABLE_CT_FAILURES()
#else
  // Otherwise, enable compile-time failures.
  #define ENABLE_CT_FAILURES() static constexpr bool GTEST_CT_TU_ENABLED = true
#endif
// =============================================================================
// Internal Utilities (in an anonymous namespace or a dedicated namespace)
// =============================================================================

namespace gtest_ct_internal {

// A simple constexpr string class.
// Adapted from Scott Schurr's "New Tools for Class and Library Authors"
// (C++Now 2012)
class str_const {
private:
  const char* const p_;
  const std::size_t sz_;

public:
  template <std::size_t N>
  explicit constexpr str_const(const char (&a)[N])
      : p_(a), sz_(N - 1) {}

  constexpr const char* getString() const { return p_; }
};

// A constexpr implementation of strcmp.
constexpr int constexpr_strcmp(const char* s1, const char* s2) {
    return (*s1 == *s2)
               ? ((*s1 == '\0') ? 0 : constexpr_strcmp(s1 + 1, s2 + 1))
               : ((*s1 < *s2) ? -1 : 1);
}

// -----------------------------------------------------------------------------
// Helper Functions and Constants
// -----------------------------------------------------------------------------

constexpr int DEFAULT_ULP_DISTANCE = 5;

// ULP-based floating-point comparison.
template <typename T>
constexpr bool almost_equal(T x, T y, int ulp = DEFAULT_ULP_DISTANCE) {
  static_assert(std::is_floating_point<T>::value,
                "almost_equal is only for floating-point types.");
  return std::abs(x - y) <= std::numeric_limits<T>::epsilon() *
                                    std::abs(x + y) * ulp ||
         std::abs(x - y) < std::numeric_limits<T>::min();
}

// Convert a character to lowercase.
constexpr char char_to_lower(char c) {
  return (c >= 'A' && c <= 'Z') ? static_cast<char>(c + ('a' - 'A')) : c;
}

// Case-insensitive string equality.
constexpr bool strcase_equal(const char* s1, const char* s2) {
    return (char_to_lower(*s1) == char_to_lower(*s2))
               ? ((*s1 == '\0') ? true : strcase_equal(s1 + 1, s2 + 1))
               : false;
}

} // namespace gtest_ct_internal

// =============================================================================
// Test Result Structure
// =============================================================================

// Expose necessary types to the global scope.
struct result {
#if __cplusplus < 202002
  constexpr result(bool assertion, gtest_ct_internal::str_const msg)
      : didTestPass{assertion}, failureMsg{msg} {}
#else
  consteval result(bool assertion, gtest_ct_internal::str_const msg)
      : didTestPass{assertion}, failureMsg{msg} {}
#endif

  const bool didTestPass;
  gtest_ct_internal::str_const failureMsg;
};

// =============================================================================
// Assertion Control Macro
// =============================================================================

#if defined(STOP_ON_CT_FAIL)
  #define ASSERT_ON_BUILD(X) static_assert(X, "gtest_ct failure: " #X);
#elif defined(CONTINUE_ON_CT_FAIL)
  #define ASSERT_ON_BUILD(X) do {} while (0);
#elif defined(GTEST_CT_TU_ENABLED) && GTEST_CT_TU_ENABLED
  #define ASSERT_ON_BUILD(X) static_assert(X, "gtest_ct failure: " #X);
#else
  #define ASSERT_ON_BUILD(X) do {} while (0);
#endif

#define STREAM_FAILURE_MSG "gtest_ct failure: " << x.failureMsg.getString()

// =============================================================================
// Compile-Time Expectation and Assertion Macros
// =============================================================================

// Note: These macros use names directly; they could be further wrapped
// in a namespace or split into a separate header if desired.

// ----- Expectations (non-fatal) -----
#define CT_EXPECT_TRUE(X)                             \
  do {                                                \
    ASSERT_ON_BUILD(X)                                \
    constexpr result x{X, gtest_ct_internal::str_const(#X)};  \
    EXPECT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG; \
  } while (0)

#define CT_EXPECT_FALSE(X) \
  do {                     \
    CT_EXPECT_TRUE(!(X));  \
  } while (0)

#define CT_EXPECT_EQ(X, Y)    \
  do {                        \
    CT_EXPECT_TRUE((X) == (Y));   \
  } while (0)

#define CT_EXPECT_NE(X, Y)      \
  do {                          \
    CT_EXPECT_FALSE((X) == (Y));    \
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
    CT_EXPECT_TRUE(gtest_ct_internal::constexpr_strcmp(X, Y) == 0);     \
  } while (0)

#define CT_EXPECT_STRNE(X, Y)                   \
  do {                                          \
    CT_EXPECT_FALSE(gtest_ct_internal::constexpr_strcmp(X, Y) == 0);    \
  } while (0)

#define CT_EXPECT_STRCASEEQ(X, Y)           \
  do {                                      \
    CT_EXPECT_TRUE(gtest_ct_internal::strcase_equal(X, Y));    \
  } while (0)

#define CT_EXPECT_STRCASENE(X, Y)           \
  do {                                      \
    CT_EXPECT_FALSE(gtest_ct_internal::strcase_equal(X, Y));   \
  } while (0)

#define CT_EXPECT_FLOAT_EQ(X, Y)               \
  do {                                         \
    CT_EXPECT_TRUE(gtest_ct_internal::almost_equal<float>(X, Y)); \
  } while (0)

#define CT_EXPECT_DOUBLE_EQ(X, Y)               \
  do {                                          \
    CT_EXPECT_TRUE(gtest_ct_internal::almost_equal<double>(X, Y)); \
  } while (0)

#define CT_EXPECT_NEAR(X, Y, abs_error)                \
  do {                                                 \
    CT_EXPECT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
  } while (0)

// ----- Assertions (fatal) -----
#define CT_ASSERT_TRUE(X)                             \
  do {                                                \
    ASSERT_ON_BUILD(X)                                \
    constexpr result x{X, gtest_ct_internal::str_const(#X)};  \
    ASSERT_TRUE(x.didTestPass) << STREAM_FAILURE_MSG; \
  } while (0)

#define CT_ASSERT_FALSE(X) \
  do {                     \
    CT_ASSERT_TRUE(!(X));  \
  } while (0)

#define CT_ASSERT_EQ(X, Y)    \
  do {                        \
    CT_ASSERT_TRUE((X) == (Y));   \
  } while (0)

#define CT_ASSERT_NE(X, Y)      \
  do {                          \
    CT_ASSERT_FALSE((X) == (Y));    \
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
    CT_ASSERT_TRUE(gtest_ct_internal::constexpr_strcmp(X, Y) == 0);     \
  } while (0)

#define CT_ASSERT_STRNE(X, Y)                   \
  do {                                          \
    CT_ASSERT_FALSE(gtest_ct_internal::constexpr_strcmp(X, Y) == 0);    \
  } while (0)

#define CT_ASSERT_STRCASEEQ(X, Y)           \
  do {                                      \
    CT_ASSERT_TRUE(gtest_ct_internal::strcase_equal(X, Y));    \
  } while (0)

#define CT_ASSERT_STRCASENE(X, Y)           \
  do {                                      \
    CT_ASSERT_FALSE(gtest_ct_internal::strcase_equal(X, Y));   \
  } while (0)

#define CT_ASSERT_FLOAT_EQ(X, Y)               \
  do {                                         \
    CT_ASSERT_TRUE(gtest_ct_internal::almost_equal<float>(X, Y)); \
  } while (0)

#define CT_ASSERT_DOUBLE_EQ(X, Y)               \
  do {                                          \
    CT_ASSERT_TRUE(gtest_ct_internal::almost_equal<double>(X, Y)); \
  } while (0)

#define CT_ASSERT_NEAR(X, Y, abs_error)                \
  do {                                                 \
    CT_ASSERT_TRUE(std::abs((X) - (Y)) <= (abs_error)); \
  } while (0)

#define CT_ASSERT_TRUE_SIMPLIFIED_FOR_TEST(X) \
  do {                                        \
    ASSERT_TRUE(X) << "Simplified CT_ASSERT_TRUE failure: " #X; \
  } while (0)

#endif  // GTEST_CT_H_
