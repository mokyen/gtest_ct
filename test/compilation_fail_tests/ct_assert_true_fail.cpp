#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_true) {
    CT_ASSERT_TRUE(false);
}
