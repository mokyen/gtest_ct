#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_strcaseeq) {
    CT_ASSERT_STRCASEEQ("foo", "FOO1");   // NOLINT(clang-diagnostic-error)
}
