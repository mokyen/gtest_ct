#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_strcasene) {
    CT_ASSERT_STRCASENE("foo", "FOO");   // NOLINT(clang-diagnostic-error)
}
