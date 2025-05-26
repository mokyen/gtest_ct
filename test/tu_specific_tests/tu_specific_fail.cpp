#include "gtest_ct.h"

// Enable compile-time failures for this translation unit
ENABLE_CT_FAILURES()

TEST(TUSpecificTests, ShouldFailAtCompileTime) {
    // Should fail at compile time. EXPECT_FATAL_FAILURE is a runtime function
    EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); }, "");
}