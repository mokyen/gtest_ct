# gtest_ct

A compile-time (CT) wrapper for Google Test

## Purpose

This header-only library is a simple wrapper for Google Test that supplies compile-time macros for compile-time testing. I created this library after being inspired by [Braden Ganetsky's talk "Unit Testing an Expression Template Library in C++20"](https://youtu.be/H4KzM-wDiQw?si=jrv5_O0MicUxFXYe) at C++Now 2024.

## Quick Example

See this in use on [Compiler Explorer](https://godbolt.org/z/n98aK6x9j).

```cpp
#include "gtest_ct.h"

constexpr int multiply(int a, int b) {
    return a * b;
}

TEST(MathTest, CompileTimeValidation) {
    // These run at compile time!
    CT_EXPECT_EQ(multiply(3, 4), 12);
    CT_ASSERT_NE(multiply(2, 5), 15);
}
```

## Requirements (EARS Syntax)

### Language & Compiler Support
**R1**: WHEN the library is included in a C++ project, the system SHALL support C++11 and all subsequent standards.

**R2**: WHEN compiling with GCC, the system SHALL support C++11, 14, 17, 20, and 23 standards.

**R3**: WHEN compiling with Clang, the system SHALL support C++11, 14, 17, 20, and 23 standards.

### Compile-Time Features
**R4**: WHEN a compile-time test fails, the system SHALL provide the ability to fail compilation immediately via global configuration.

**R5**: WHERE different translation units require different behavior, the system SHALL allow enabling/disabling compile-time failures per translation unit, with global configuration taking precedence.

**R6**: WHEN runtime reporting is preferred, the system SHALL collect compile-time failures and report them during unit test execution, ensuring:
- **R6.1**: All compile-time errors are caught and reported without missing any
- **R6.2**: Compile-time and runtime results can be compared for validation

**R7**: WHEN compile-time failure mode is enabled, both CT_ASSERT_* and CT_EXPECT_* SHALL behave identically and stop execution on failure.

### Test Interface
**R8**: WHEN users write test assertions, the system SHALL provide syntax that matches existing Google Test assertion patterns.

**R8**: WHEN using compile-time CT_ASSERT_* and CT_EXPECT_* calls, the system SHALL:
- **R8.1**: Behave identically when compile-time failure mode is enabled (both stop on failure)
- **R8.2**: Make CT_ASSERT_* abort test execution on failure in runtime reporting mode, while CT_EXPECT_* continues, matching Google Test behavior

**R9**: WHERE test failures occur, the system SHALL support custom failure messages with the same syntax as Google Test.

### Test Coverage
**R10**: WHEN performing comparisons, the system SHALL provide complete coverage of comparison operations (EQ, NE, LT, LE, GT, GE).

**R11**: WHEN testing floating-point values, the system SHALL support floating-point specific comparisons (FLOAT_EQ, DOUBLE_EQ).

**R12**: WHEN comparing strings, the system SHALL support both case-sensitive and case-insensitive string comparisons (STREQ, STRNE, STRCASEEQ, STRCASENE).

**R13**: WHEN testing approximate equality, the system SHALL support near-equality testing with configurable tolerance (NEAR).

## Requirements Traceability

| Req ID | Description | Test Location | Test Description |
|--------|-------------|---------------|------------------|
| R1-R3  | C++/Compiler Support | CI Pipeline | Matrix build testing all compiler/standard combinations |
| R4     | CT Error Fails Build | compilation_fail_tests/ | All CT_ASSERT tests verify build failure |
| R5     | Per-TU CT Failures | tu_specific_tests/ | Tests enabling/disabling per translation unit |
| R6     | RT Reporting | passing_tests/passing_tests.cpp | CT_EXPECT_FAILURE_TESTS verify RT reporting |
| R7     | CT Failure Behavior | compilation_fail_tests/ | Both CT_ASSERT and CT_EXPECT stop on failure |
| R8     | ASSERT/EXPECT | passing_tests/passing_tests.cpp | CT_ASSERT_TESTS & CT_EXPECT_TESTS |
| R9     | Custom Messages | passing_tests/passing_tests.cpp |  Custom gtest-style failure messages |
| R10    | Comparisons | compilation_fail_tests/ | EQ, NE, LT, LE, GT, GE tests |
| R11    | Floating-Point | compilation_fail_tests/ | FLOAT_EQ, DOUBLE_EQ, NEAR tests |
| R12    | Strings | compilation_fail_tests/ | STREQ, STRNE, STRCASEEQ, STRCASENE |
| R13    | Near Testing | compilation_fail_tests/ | CT_ASSERT_NEAR test cases |

## Why Compile-Time Testing?

**Catch Errors Earlier**: Issues are found during compilation, not when your program runs.

**Verify constexpr Code**: Ensure your compile-time functions actually work at compile time.

**No Undefined Behavior**: Compilers reject undefined behavior during constant evaluation, catching dangerous constructs that might pass runtime testing.

**Template Validation**: Test your template metaprogramming and expression templates thoroughly.

**Faster Feedback**: No need to run tests to find basic logic errors.

**Cross-Compiler Consistency**: Some compilers may perform different calculations at compile time than at runtime - compile-time testing helps catch these discrepancies.

**Consistent Results**: Same test outcomes across all environments and builds.

## Key Features

- **Broad Compiler Support**: Works with GCC and Clang across C++11 through C++23
- **CMake Integration**: Full CMake support for easy project integration
- **Flexible Failure Modes**: Choose between immediate compilation failure or runtime reporting
- **Per-Translation Unit Control**: Configure behavior differently for different source files, with global override capability
- **Complete Test Coverage**: All major comparison types including floating-point and strings
- **Google Test Compatible**: CT_ASSERT_* and CT_EXPECT_* syntax matching Google Test patterns
- **Header-Only**: Just include and go
- **Thoroughly Tested**: Comprehensive CI testing across compiler/standard combinations

## Configuration Options

```cpp
// Option 1: Runtime reporting (default) - collect failures for runtime reporting
#include "gtest_ct.h"

// Option 2: Stop compilation on any CT test failure
#define STOP_ON_CT_FAIL
#include "gtest_ct.h"

// Option 3: Per-translation unit configuration
// Global STOP_ON_CT_FAIL overrides local settings
ENABLE_CT_FAILURES(); // Enable for this translation unit
#include "gtest_ct.h"
```

## Testing and Validation

The gtest_ct library is thoroughly tested in continuous integration across all supported compiler and standard combinations. 

**Running Tests Locally**: Tests can be run locally for validation, but due to the processor-intensive nature of compilation-failure tests, it's recommended to run these periodically rather than on every build.

**CI Integration**: For projects using gtest_ct, consider running the library's test suite periodically with your specific build configuration to ensure compatibility, but avoid running on every build due to performance impact.

## Benefits for High-Reliability Software

Moving testing to compile time provides several advantages for software where correctness is critical:

- **Consistent Results**: Same behavior across all environments and builds
- **Early Detection**: Prevents deployment of code with logical errors
- **Validation Evidence**: Compilation success provides objective proof of correctness
- **Risk Mitigation**: Catches undefined behavior that could cause unpredictable failures

For detailed guidance on using gtest_ct in regulated industries, see [SAFETY_CRITICAL.md](SAFETY_CRITICAL.md).

## Future Improvements

- Expanded compiler support (MSVC, ICC)
- Bazel build system support
- Parameterized test support
- Integration with static analysis tools  
- Support for testing template metaprogramming
- Automated documentation generation for compliance workflows

## Quality & Security

[![OpenSSF Scorecard](https://api.scorecard.dev/projects/github.com/mokyen/gtest_ct/badge)](https://scorecard.dev/viewer/?uri=github.com/mokyen/gtest_ct)

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## License

[Your license information here]