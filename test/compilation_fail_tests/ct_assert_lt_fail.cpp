#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_lt) {
    CT_ASSERT_LT(2, 1);   // NOLINT(clang-diagnostic-error)
}
