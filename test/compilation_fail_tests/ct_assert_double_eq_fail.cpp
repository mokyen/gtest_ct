#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_double_eq) {
    CT_ASSERT_DOUBLE_EQ(1.0, 2.0);
}
