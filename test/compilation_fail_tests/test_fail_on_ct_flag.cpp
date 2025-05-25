// Make sure the “fail‐on‐CT‐fail” mode is active.
#define STOP_ON_CT_FAIL

#include "gtest_ct.h" // or wherever your header lives

// int main() {
//     // This line is supposed to fail at compile time (via static_assert):
//     constexpr bool res = almost_equal<float>(0.1f, 0.1f + 0.0f);  

//     CT_ASSERT_TRUE(true);
//     CT_ASSERT_TRUE(false);
//     // … OR perhaps a custom call in your library that does
//     // static_assert(true, "expected‐compile‐failure");
//     return 0;
// }

TEST(CompileTimeTests, Example) {
    // CT_ASSERT_TRUE(true);
    // CT_ASSERT_TRUE(false);  // This will fail the test at runtime, not compile time.
    static_assert(false);  // This will cause a compile-time error.
}