#include "gtest_ct.h"

//=================================================
// Testing usage
//=================================================

constexpr int foo (int x) { return x; }

class TestStruct
{
public:
    constexpr TestStruct(int c, int d) : a{c}, b{d}
    {}
    constexpr bool operator==(const TestStruct& rhs) const { return (this->a == rhs.a) && (this->b == rhs.b); }

private:
    int a, b;
};

TEST(CT_EXPECT_TESTS, BASICS)
{
    constexpr bool t{true};
    CT_EXPECT_TRUE(t);
    constexpr bool f{false};
    CT_EXPECT_FALSE(f);

    CT_EXPECT_EQ(true, true);
    CT_EXPECT_NE(true, false);

    CT_EXPECT_EQ(1, 1);
    CT_EXPECT_NE(1, 2);

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    CT_EXPECT_EQ(A, A);
    CT_EXPECT_EQ(A, B);
    CT_EXPECT_NE(A, C);
}

TEST(CT_ASSERT_TESTS, BASICS)
{
    constexpr bool t{true};
    CT_ASSERT_TRUE(t);
    constexpr bool f{false};
    CT_ASSERT_FALSE(f);

    CT_ASSERT_EQ(true, true);
    CT_ASSERT_NE(true, false);

    CT_ASSERT_EQ(1, 1);
    CT_ASSERT_NE(1, 2);

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    CT_ASSERT_EQ(A, A);
    CT_ASSERT_EQ(A, B);
    CT_ASSERT_NE(A, C);
}


TEST(CT_EXPECT_FAILURE_TESTS, BASICS)
{
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_TRUE(false); },"");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_FALSE(true); },"");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_EQ(1, 2); },"");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(1, 1); },"");

    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(A, A); },"");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_NE(A, B); },"");
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_EQ(A, C); },"");
}

//TODO WIP
TEST(CT_ASSERT_FAILURE_TESTS, BASICS2)
{
    EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); },"");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_FALSE(true); },"");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(1, 2); },"");
    EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(1, 1); },"");
    
    constexpr TestStruct A{1, 2};
    constexpr TestStruct B{1, 2};
    constexpr TestStruct C{2, 2};

    //TODO not working yet
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, A); },"");
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_NE(A, B); },"");
    // EXPECT_FATAL_FAILURE({ CT_ASSERT_EQ(A, C); },"");
}

TEST(CT_EXPECT_TESTS, CT_EXPECT_CONTINUES)
{
    CT_EXPECT_TRUE(true);
    //This would fail if we didn't continue after the previous test
    EXPECT_NONFATAL_FAILURE({ CT_EXPECT_TRUE(false); },"");
}

TEST(CT_EXPECT_TESTS, COMBINED_CT_RT_EXPECT)
{
    CT_EXPECT_TRUE(true);
    //This would fail if we didn't continue after the previous test
    EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); },"");
}

TEST(CT_ASSERT_TESTS, CT_ASSERT_DOESNT_CONTINUE)
{
    EXPECT_FATAL_FAILURE({ CT_ASSERT_TRUE(false); },"");
    //This would fail if we continued after the previous test
    //TODO this isn't working as expected
    EXPECT_TRUE(false) << "This shouldn't be evaluated";
}

TEST(CT_ASSERT_TESTS, COMBINED_CT_RT_EXPECT)
{
    CT_ASSERT_TRUE(true);
    //This would fail if we didn't continue after the previous test
    EXPECT_NONFATAL_FAILURE({ EXPECT_TRUE(false); },"");
}

/*
TODO Tests to write
NO FAIL COMPILATION ON CT FAILS
X* basic CT expect_true/assert true passes
X* basic CT expect_true false causes fail
X* basic CT expect_false/assert false passes
X* basic CT expect_false true causes fail

X* basic CT expect_eq/assert_eq true equals true passes
X* basic CT expect_eq/assert_eq false equals false passes
X* basic CT expect_eq/assert_eq true equals false fails
X* basic CT expect_eq/assert_eq int equals same int passes
X* basic CT expect_eq/assert_eq int equals different int fails
X* basic CT expect_eq/assert_eq objects

X* inverse of last grouping with _ne

* assert test(s) showing that results stop after assert fail
X* expect test(s) showing that results continue after test fail

X* test(s) showing interweaving CT and RT tests EXPECT
* test(s) showing interweaving CT and RT tests Assert


FAIL COMPILATION ON CT FAILS
* show that expect/assert tests fail compilation


*/