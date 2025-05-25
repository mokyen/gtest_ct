#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_near) {
    CT_ASSERT_NEAR(1.0, 2.0, 0.1);
}
