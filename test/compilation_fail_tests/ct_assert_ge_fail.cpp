#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_ge) {
    CT_ASSERT_GE(3, 2);
}
