#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_ne) {
    CT_ASSERT_NE(1, 1);
}
