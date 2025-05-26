#include "gtest_ct.h"

// Enable compile-time failures for this translation unit
ENABLE_CT_FAILURES()

TEST(TUSpecificTests, ShouldFailAtCompileTime) {
    CT_ASSERT_TRUE(false);  // Should fail at compile time
}