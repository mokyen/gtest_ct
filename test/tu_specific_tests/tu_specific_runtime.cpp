#include "gtest_ct.h"

// No ENABLE_CT_FAILURES() call, so this will fail at runtime

TEST(TUSpecificTests, ShouldFailAtRuntime) {
   EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
}