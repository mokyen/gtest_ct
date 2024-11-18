# gtest_ct

A compile-time (CT) wrapper for google test

## Purpose

This header-only library is a simple wrapper for google test that supplies some compile-time macros for compile-time testing. I created this library after being inspired by [Braden Ganetsky's talk "Unit Testing an Expression Template Library in C++20"](https://youtu.be/H4KzM-wDiQw?si=jrv5_O0MicUxFXYe) at C++Now 2024.

### Example of usage:

See this in use on [Compiler Explorer](https://godbolt.org/z/n98aK6x9j).

The requirements of this library include:

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

## Future improvements

* Ability to enable/disable failing a build on a CT test failure per compilation unit
