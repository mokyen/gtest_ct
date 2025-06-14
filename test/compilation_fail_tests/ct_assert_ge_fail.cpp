#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_ge) {
    CT_ASSERT_GE(1, 2);   // NOLINT(clang-diagnostic-error)
}
