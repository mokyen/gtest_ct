# gtest_ct
A compile-time (CT) wrapper for google test

## Purpose

This header-only library is a simple wrapper for google test that supplies some compile-time macros for compile-time testing. The requirements of this library include:

### Requirements

* Support for C++11 and beyond
* Ability to choose to fail a compilation on a CT error
* Ability to choose to not fail builds on CT failures but instead store the results and report them at RT
  * This allows all CT errors to be caught and reported
  * This also allows CT and RT results to be compared
* Ability to easily choose between the CT-fail and RT reporting option
* Assertion syntax matching existing gtest assertions
* Support for a CT ASSERT_* and EXPECT_* calls
  * These will act the same when we enable failing on a CT failure
  * The ASSERT will abort a test on a failure when we enable the RT reporting, similar to ASSERT_* in gtest
* Support custom failure messages like gtest

## Benefits of runtime testing

Moving functionality from RT to CT has become an increasing trend in modern C++ development since constexpr was introduced in C++11. CT operations can improve code efficiency, since, and safety. The benefits of moving our testing to CT include:

* Undefined behavior is not permitted at CT
  * This may catch errors that might not be observed until RT
* Testing parts of CT operations may help when creating CT chains of operations
* Failing builds on CT testing failures ensures that tests are run
* CT tests may be faster in some cases
* Some compilers may perform different calculations at CT than at RT, and these results are difficult catch without CT testing
