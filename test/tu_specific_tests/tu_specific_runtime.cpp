#include "gtest_ct.h"

// No ENABLE_CT_FAILURES() call, so this will fail at runtime

TEST(TUSpecificTests, ShouldFailAtRuntime) {
    // Should fail at run time. EXPECT_FATAL_FAILURE is a runtime function
   EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
}