# Introduction
This is an integration test of Abseil in a Modern [CMake](https://cmake.org/) C++ Project using
 [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html) module.

We try to integrate abseil-cpp using `add_subdirectory(abseil-cpp)` **or** by installing it first (in astaging area) then using `find_package(absl)`.

This project should run on Linux, Mac and Windows.

# CMake Dependencies Tree
This CMake project is composed of one executable (FooApp) and one library (Foo)
with the following dependencies:  
```
absl:
Foo: absl::strings
FooApp: Foo, absl::strings
```

# Strategy 1: `add_subdirectory(abseil-cpp)`
[![Build Status](https://travis-ci.org/Mizux/cmake-abseil.svg?branch=add_subdirectory)](https://travis-ci.org/Mizux/cmake-abseil)
[![Build status](https://ci.appveyor.com/api/projects/status/fxxmf49bkboftmg5/branch/add_subdirectory?svg=true)](https://ci.appveyor.com/project/Mizux/cmake-abseil/branch/add_subdirectory)

To see the integration of abseil-cpp as `add_subdirectory()` please take a look
at the branch [`add_subdirectory`](https://github.com/Mizux/cmake-abseil/tree/add_subdirectory)

**spoiler: This is not working (as intended)**

# Strategy 2: `find_package(absl)`
[![Build Status](https://travis-ci.org/Mizux/cmake-abseil.svg?branch=install)](https://travis-ci.org/Mizux/cmake-abseil)
[![Build status](https://ci.appveyor.com/api/projects/status/fxxmf49bkboftmg5/branch/install?svg=true)](https://ci.appveyor.com/project/Mizux/cmake-abseil/branch/install)

To see the integration of abseil-cpp using `find_package()` (and local staging install) please take a look
at the branch [`install`](https://github.com/Mizux/cmake-abseil/tree/install)

**spoiler: This is the way to go**

# Known issues

On windows, abseil-cpp link flags `/ignore:4221` break the integration see [abseil-cpp#293](https://github.com/abseil/abseil-cpp/issues/293)

# Contributing
The [CONTRIBUTING.md](./CONTRIBUTING.md) file contains instructions on how to
file the Contributor License Agreement before sending any pull requests (PRs).
Of course, if you're new to the project, it's usually best to discuss any
proposals and reach consensus before sending your first PR.

# License
Apache 2. See the LICENSE file for details.

# Disclaimer
This is not an official Google product, it is just code that happens to be
owned by Google.
