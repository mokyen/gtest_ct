#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_eq) {
    CT_ASSERT_EQ(1, 2);
}
