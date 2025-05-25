#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_strne) {
    CT_ASSERT_STRNE("foo", "foo");
}
