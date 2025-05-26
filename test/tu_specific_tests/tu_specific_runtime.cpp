#include "gtest_ct.h"

// No ENABLE_CT_FAILURES() call, so this will fail at runtime

TEST(TUSpecificTests, ShouldFailAtRuntime) {
    CT_ASSERT_TRUE(false);  // This will fail during test execution
}