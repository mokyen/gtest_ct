#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

TEST(CompileTimeTests, ExpectFailTest_false) {
    CT_ASSERT_FALSE(true);  // NOLINT(clang-diagnostic-error)
}
