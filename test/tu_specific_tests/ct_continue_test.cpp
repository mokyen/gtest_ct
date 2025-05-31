#define CONTINUE_ON_CT_FAIL
#include "gtest_ct.h"
// Enable compile-time failures for this translation unit
ENABLE_CT_FAILURES()

TEST(CompileTimeTests, ContinueOnFailTest) {
    CT_ASSERT_TRUE(false);  // This should NOT stop compilation
    CT_ASSERT_EQ(1, 2);    // This should also continue
    CT_ASSERT_TRUE(true);  // This should be reachable
}