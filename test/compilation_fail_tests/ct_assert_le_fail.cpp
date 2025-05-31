#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_le) {
    CT_ASSERT_LE(2, 1);   // NOLINT(clang-diagnostic-error)
}
