# Safety-Critical Development with gtest_ct

This document provides guidance for using gtest_ct in regulated industries where software failures can have life-threatening consequences, including medical devices (FDA), automotive (ISO 26262), and aviation (DO-178C).

## Regulatory Context

In safety-critical software development, validation requires demonstrable evidence of correctness. Traditional testing approaches may not provide sufficient assurance for systems where failure could result in injury or death. Compile-time testing offers additional verification capabilities that align with regulatory requirements.

## Additional Requirements for Safety-Critical Use

Beyond the basic requirements R1-R14 in the README, safety-critical applications should consider these additional requirements. Requirements are specified using [EARS (Easy Approach to Requirements Syntax)](https://alistairmavin.com/ears/) for clarity and testability.

**R13 - Traceability**: WHEN compile-time tests execute, the system SHALL provide traceable results that can be included in validation documentation.

**R14 - Comprehensive Testing**: WHEN validating safety functions, the system SHALL enable testing of critical boundary conditions and failure modes at compile time.

## Requirements Traceability

Complete traceability matrix covering all requirements R1-R14:

| Req ID | Description | Test Location | Test Description |
|--------|-------------|---------------|------------------|
| R1-R2  | C++/Compiler Support | CI Pipeline | Matrix build testing GCC 10+ and Clang 20+ across C++ standards |
| R3     | CT Error Fails Build | compilation_fail_tests/ | All CT_ASSERT tests verify build failure |
| R4     | Global Runtime Override | CI Pipeline | CONTINUE_ON_CT_FAIL flag testing |
| R5     | RT Reporting | passing_tests/passing_tests.cpp | CT_EXPECT_FAILURE_TESTS verify RT reporting |
| R6     | ASSERT/EXPECT Behavior | passing_tests/passing_tests.cpp | CT_ASSERT_TESTS & CT_EXPECT_TESTS |
| R7     | GTest Syntax | passing_tests/passing_tests.cpp | Syntax compatibility validation |
| R8     | Custom Messages | passing_tests/passing_tests.cpp | Custom gtest-style failure messages |
| R9     | Comparisons | compilation_fail_tests/ | EQ, NE, LT, LE, GT, GE tests |
| R10    | Floating-Point | compilation_fail_tests/ | FLOAT_EQ, DOUBLE_EQ tests |
| R11    | Strings | compilation_fail_tests/ | STREQ, STRNE, STRCASEEQ, STRCASENE |
| R12    | Near Testing | compilation_fail_tests/ | CT_ASSERT_NEAR test cases |
| R13    | Traceability | This document | Requirements mapping and test references |
| R14    | Boundary Testing | User implementation | Framework supports boundary condition testing |

## Risk Assessment Framework

### Third-Party Library Risk Assessment Template

When evaluating gtest_ct (or any testing library) for safety-critical use, consider these risk categories:

**Functional Risk Assessment**:
- *Risk*: Testing library produces false positives/negatives
- *Mitigation*: Extensive validation against known-good test cases; traceability matrix verification
- *Residual Risk*: Low - library only affects test execution, not production code

**Integration Risk Assessment**:
- *Risk*: Compile-time testing masks runtime issues
- *Mitigation*: Use as complement to, not replacement for, runtime testing
- *Residual Risk*: Medium - requires process discipline to maintain both test types

**Supply Chain Risk Assessment**:
- *Risk*: Malicious code injection or unmaintained dependencies
- *Mitigation*: OpenSSF scorecard monitoring; source code review; controlled dependency management
- *Residual Risk*: Low - header-only library with minimal dependencies

**Process Risk Assessment**:
- *Risk*: Developers bypass compile-time tests when they fail
- *Mitigation*: CI/CD integration preventing builds on test failures; code review processes
- *Residual Risk*: Medium - requires organizational discipline

### Note on Context-Dependent Risk

The actual risk level of using gtest_ct depends entirely on:
- **What you're testing**: Critical safety functions vs. utility code
- **Your system's failure modes**: What happens when the tested code fails?
- **Your development process**: How are test failures handled?
- **Your regulatory environment**: FDA Class III vs. Class I device requirements

A testing library's risks are inherently tied to the criticality of the code being tested and the consequences of test failures going undetected.

### Functional Safety Considerations

**Systematic Failures**: Use compile-time testing to verify algorithmic correctness and prevent systematic errors that could affect entire product populations.

**Random Hardware Failures**: While compile-time testing cannot prevent hardware failures, it can verify that software correctly handles error conditions and maintains safe states.

**Common Cause Failures**: Compile-time validation helps ensure diverse implementations produce consistent results, reducing common cause failure risks.

### Cybersecurity Integration

**Supply Chain Security**: The OpenSSF Scorecard integration provides automated assessment of project security practices, addressing FDA and other regulatory concerns about third-party components.

**Static Analysis**: Compile-time testing complements static analysis tools by providing executable verification of security-relevant code paths.

## Validation Support

The gtest_ct library provides structured requirements and traceability matrices to support validation processes in regulated environments. Rather than dictating specific validation methodologies, the library provides inputs that can be integrated into existing validation frameworks:

**Requirements Structure**: All functional requirements use EARS syntax for clarity and testability
**Traceability Matrix**: Direct mapping between requirements and test implementations  
**Test Validation**: Library tests can be run with your specific build configuration to ensure compatibility

**Recommended Practice**: Run the gtest_ct test suite periodically with your target compilation environment to validate compatibility, but avoid running these processor-intensive tests on every build.

### Test Categories for Safety-Critical Systems

**Boundary Value Testing**: Verify behavior at operational limits
```cpp
CT_EXPECT_EQ(safe_function(MAX_INPUT), EXPECTED_MAX_OUTPUT);
// Note: Exception testing not currently supported
```

**State Machine Validation**: Verify state transitions at compile time
```cpp
constexpr auto state_machine = build_safety_state_machine();
CT_EXPECT_EQ(state_machine.transition(SAFE, ALARM_INPUT), ALARM_STATE);
```

**Cross-Compilation Validation**: **(Theoretical - not yet validated)** When developing for embedded targets, compile-time tests can execute using the actual target compiler in CI environments, providing validation without requiring hardware execution or complex cross-platform test orchestration.

## Using gtest_ct in Regulated Environments

The library serves as a tool that can be integrated into existing safety-critical development processes rather than defining those processes. Key integration points include:

**Configuration Management**: Version control test specifications alongside requirements
**Validation Evidence**: Compile-time test results provide objective evidence of software behavior
**Risk Mitigation**: Early detection of undefined behavior and logic errors
**Traceability**: Clear mapping between requirements and test implementation

### Integration Considerations

**CI/CD Integration**: Include periodic validation runs with your target build configuration
**Risk Assessment**: Consider compile-time testing as one component of your overall risk mitigation strategy
**Process Integration**: Incorporate compile-time testing into existing validation workflows

## Example: Safety-Critical Test Implementation

```cpp
#include "gtest_ct.h"
#include "safety_functions.h"

// Enable compile-time failure mode for safety-critical validation
#define STOP_ON_CT_FAIL
ENABLE_CT_FAILURES();

class SafetyCriticalTest : public ::testing::Test {
protected:
    static constexpr double SAFETY_MARGIN = 0.1;
    static constexpr int MAX_SAFE_VALUE = 1000;
};

TEST_F(SafetyCriticalTest, BoundaryValueValidation) {
    // REQ_SF_001: System shall operate safely within defined limits
    CT_EXPECT_LE(safety_function(MAX_SAFE_VALUE), MAX_SAFE_VALUE + SAFETY_MARGIN);
    // Note: Exception testing not currently supported in gtest_ct
}

TEST_F(SafetyCriticalTest, StateValidation) {
    // REQ_SF_002: System shall maintain safe states
    CT_EXPECT_EQ(get_safety_state_on_input(NORMAL_INPUT), SAFE_STATE);
    CT_EXPECT_EQ(get_safety_state_on_input(BOUNDARY_INPUT), SAFE_STATE);
}
```

## Conclusion

This document demonstrates how open source libraries can incorporate practices from regulated industries without compromising innovation. By providing structured approaches to validation and quality management, OSS projects can support adoption in safety-critical applications while maintaining the collaborative development model that makes open source powerful.

The gtest_ct library serves as a practical example of bridging these worlds—offering the rigor needed for life-critical systems while remaining accessible to the broader C++ community.
