#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_float_eq) {
    CT_ASSERT_FLOAT_EQ(1.0f, 2.0f);
}
