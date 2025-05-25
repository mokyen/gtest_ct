#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_gt) {
    CT_ASSERT_GT(1, 2);
}
