#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_streq) {
    CT_ASSERT_STREQ("foo", "bar");   // NOLINT(clang-diagnostic-error)
}
