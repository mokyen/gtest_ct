# gtest_ct

A compile-time (CT) wrapper for google test

## Purpose

This header-only library is a simple wrapper for google test that supplies some compile-time macros for compile-time testing. I created this library after being inspired by [Braden Ganetsky's talk "Unit Testing an Expression Template Library in C++20"](https://youtu.be/H4KzM-wDiQw?si=jrv5_O0MicUxFXYe) at C++Now 2024.

### Example of usage:

See this in use on [Compiler Explorer](https://godbolt.org/z/n98aK6x9j).

### Requirements

#### Language & Compiler Support
* R1: Support for C++11 and beyond
* R2: Support for GCC compiler (C++11, 14, 17, 20, 23)
* R3: Support for Clang compiler (C++11, 14, 17, 20, 23)

#### Compile-Time Features
* R4: Ability to choose to fail a compilation on a CT error
* R5: Ability to enable/disable CT failures per translation unit
* R6: Ability to choose to not fail builds on CT failures but report at runtime
  * R6.1: Allows all CT errors to be caught and reported
  * R6.2: Allows CT and RT results to be compared
* R7: Ability to easily switch between CT-fail and RT reporting options

#### Test Interface
* R8: Assertion syntax matching existing gtest assertions
* R9: Support for CT ASSERT_* and EXPECT_* calls
  * R9.1: Act identically when CT failure is enabled
  * R9.2: ASSERT aborts test on failure in RT mode (like gtest)
* R10: Support custom failure messages like gtest

#### Test Coverage
* R11: Complete coverage of comparison operations
* R12: Support for floating-point comparisons
* R13: Support for string comparisons (case-sensitive/insensitive)
* R14: Support for near-equality testing

### Requirements Traceability

| Req ID | Description | Test Location | Test Description |
|--------|-------------|---------------|------------------|
| R1-R3  | C++/Compiler Support | CI Pipeline | Matrix build testing all compiler/standard combinations |
| R4     | CT Error Fails Build | compilation_fail_tests/ | All CT_ASSERT tests verify build failure |
| R5     | Per-TU CT Failures | tu_specific_tests/ | Tests enabling/disabling per translation unit |
| R6     | RT Reporting | passing_tests/passing_tests.cpp | CT_EXPECT_FAILURE_TESTS verify RT reporting |
| R7     | CT/RT Switching | tu_specific_tests/ | Tests both modes in different TUs |
| R8     | GTest Syntax | passing_tests/passing_tests.cpp | All test macros mirror GTest naming |
| R9     | ASSERT/EXPECT | passing_tests/passing_tests.cpp | CT_ASSERT_TESTS & CT_EXPECT_TESTS |
| R10    | Custom Messages | passing_tests/passing_tests.cpp | Failure message verification in tests |
| R11    | Comparisons | compilation_fail_tests/ | EQ, NE, LT, LE, GT, GE tests |
| R12    | Floating-Point | compilation_fail_tests/ | FLOAT_EQ, DOUBLE_EQ, NEAR tests |
| R13    | Strings | compilation_fail_tests/ | STREQ, STRNE, STRCASEEQ, STRCASENE |
| R14    | Near Testing | compilation_fail_tests/ | CT_ASSERT_NEAR test cases |

## Benefits of Compile-Time Testing

Moving functionality from RT to CT has become an increasing trend in modern C++ development since constexpr was introduced in C++11. CT operations can improve code efficiency and safety. The benefits of moving our testing to CT include:

* Undefined behavior is not permitted at CT
  * This may catch errors that might not be observed until RT
* Testing parts of CT operations may help when creating CT chains of operations
* Failing builds on CT testing failures ensures that tests are run
* CT tests may be faster in some cases
* Some compilers may perform different calculations at CT than at RT, and these results are difficult to catch without CT testing

## Medical Device Development Applications

See MEDICAL_DEVICES.md for detailed information about how this library can be beneficial in medical device development, including:
- Early detection of potential runtime errors
- Improved test coverage documentation
- Support for validation requirements

## Future Improvements

* Expanded compiler support (MSVC, ICC)
* Integration with static analysis tools
* Support for testing template metaprogramming

[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/mokyen/gtest_ct/badge)](https://scorecard.dev/viewer/?uri=github.com/mokyen/gtest_ct)