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

## Requirements

Requirements are specified using [EARS (Easy Approach to Requirements Syntax)](https://alistairmavin.com/ears/) for clarity and testability.

### Language & Compiler Support
**R1**: WHEN the library is included in a C++ project, the system SHALL support C++11 and all subsequent standards.

**R2**: WHEN compiling with GCC, the system SHALL support C++11, 14, 17, 20, and 23 standards.

**R3**: WHEN compiling with Clang, the system SHALL support C++11, 14, 17, 20, and 23 standards.

### Compile-Time Features
**R4**: WHEN a compile-time test fails, the system SHALL provide the ability to fail compilation immediately via global configuration.

**R5**: WHERE different translation units require different behavior, the system SHALL allow enabling/disabling compile-time failures per translation unit, with global configuration taking precedence.

**R6**: WHEN runtime reporting is preferred, the system SHALL collect compile-time failures and report them during unit test execution.

**R7**: WHEN compile-time failure mode is enabled, both CT_ASSERT_* and CT_EXPECT_* SHALL behave identically and stop execution on failure.

### Test Interface
**R8**: WHEN users write test assertions, the system SHALL provide syntax that matches existing Google Test assertion patterns.

**R9**: WHEN using compile-time CT_ASSERT_* and CT_EXPECT_* calls, the system SHALL:
- **R9.1**: Behave identically when compile-time failure mode is enabled (both stop on failure)
- **R9.2**: Make CT_ASSERT_* abort test execution on failure in runtime reporting mode, while CT_EXPECT_* continues, matching Google Test behavior

**R10**: WHERE test failures occur, the system SHALL support custom failure messages with the same syntax as Google Test.

### Test Coverage
**R11**: WHEN performing comparisons, the system SHALL provide complete coverage of comparison operations (EQ, NE, LT, LE, GT, GE).

**R12**: WHEN testing floating-point values, the system SHALL support floating-point specific comparisons (FLOAT_EQ, DOUBLE_EQ).

**R13**: WHEN comparing strings, the system SHALL support both case-sensitive and case-insensitive string comparisons (STREQ, STRNE, STRCASEEQ, STRCASENE).

**R14**: WHEN testing approximate equality, the system SHALL support near-equality testing with configurable tolerance (NEAR).

## Why Compile-Time Testing?

**Catch Errors Earlier**: Issues are found during compilation, not when your program runs.

**Verify constexpr Code**: Ensure your compile-time functions actually work at compile time.

**No Undefined Behavior**: Compilers reject undefined behavior during constant evaluation, catching dangerous constructs that might pass runtime testing.

**Template Validation**: Test your template metaprogramming and expression templates thoroughly.

**Faster Feedback**: No need to run tests to find basic logic errors.

**Cross-Compiler Consistency**: Some compilers may perform different calculations at compile time than at runtime - compile-time testing helps catch these discrepancies.

**Cross-Compilation Testing**: **(Theoretical - not yet validated)** When cross-compiling for embedded targets, compile-time tests can run using the actual target compiler in your CI environment, providing validation without requiring hardware or target system execution. This could enable automated testing with the real target toolchain while maintaining CI automation and audit trails required for regulated environments.

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

- **Early Detection**: Prevents deployment of code with logical errors
- **Validation Evidence**: Compilation success provides objective proof of correctness
- **Risk Mitigation**: Catches undefined behavior that could cause unpredictable failures
- **Target Compiler Validation**: **(Theoretical)** Enables testing with actual target compiler in cross-compilation scenarios

For detailed guidance on using gtest_ct in regulated industries, see [SAFETY_CRITICAL.md](SAFETY_CRITICAL.md).

## Future Improvements

- Expanded compiler support (MSVC, ICC)
- Bazel build system support
- Parameterized test support
- Integration with static analysis tools  
- Support for testing template metaprogramming
- Automated report generation for compliance workflows
- Global override flag to disable compile-time failure mode
- Fuzzing integration (exploring applicability to compile-time testing)
- Cross-compilation testing validation (currently theoretical)

## Quality & Security

Working to improve [OpenSSF Scorecard](https://scorecard.dev/viewer/?uri=github.com/mokyen/gtest_ct) rating.

## Contributing

We welcome contributions! Please submit pull requests or create issues for bugs, feature requests, or improvements.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.