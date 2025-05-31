#define STOP_ON_CT_FAIL
#define CONTINUE_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ConflictingFlagsTest) {
    CT_ASSERT_TRUE(true);  // Should never reach here due to #error
}