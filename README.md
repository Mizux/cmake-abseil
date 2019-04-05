[![Build Status](https://travis-ci.org/Mizux/cmake-abseil.svg?branch=add_subdirectory)](https://travis-ci.org/Mizux/cmake-abseil)
[![Build status](https://ci.appveyor.com/api/projects/status/fxxmf49bkboftmg5/branch/add_subdirectory?svg=true)](https://ci.appveyor.com/project/Mizux/cmake-abseil/branch/add_subdirectory)

# Strategy 1: `add_subdirectory(abseil-cpp)`

## Introduction
This is an integration test of Abseil in a Modern [CMake](https://cmake.org/) C++ Project using
 [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html) module.

We try to integrate abseil-cpp as a project subdirectory.

This project support Linux Distro, MacOS and Windows (VS2015/2017).
**spoiler: This is not working (as intended)**

## CMake Dependencies Tree
This CMake project is composed of one executable (FooApp) and one library (Foo)
with the following dependencies:  
```
absl:
Foo: absl::strings
FooApp: Foo, absl::strings
```

### Project directory layout
Thus the project layout is as follow:

* [CMakeLists.txt](CMakeLists.txt) Top-level for [CMake](https://cmake.org/cmake/help/latest/) based build doing the orchestration.
* [cmake](cmake) Subsidiary CMake files.
 cmake
* [Foo](Foo) Root directory for `Foo` source code.
  * [CMakeLists.txt](CMakeLists.txt) CMake file for `Foo`.
  * [include/foo](include/foo) Public include directory for `Foo`.
    * [Foo.hpp](include/foo/Foo.hpp) Public header for `Foo`.
  * [src/Foo.cpp](src/Foo.cpp) Private source for `Foo`.
* [FooApp](FooApp) Root directory for `FooApp` source code.
  * [CMakeLists.txt](CMakeLists.txt) CMake file for `FooApp`.
  * [src/main.cpp](src/main.cpp) Private source for `FooApp`.
* [ci](ci) Top-level directory for Makefile/docker Continous Integration testing.

## C++ Project Build
To build the C++ project, as usual:
```sh
cmake -H. -Bbuild -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build build
```

## Known issues
* Export set do a closure on **non** `IMPORTED` targets. So it won't work.
You should see this type of error.
```sh
CMake Error: install(EXPORT "CMakeAbseilTargets" ...) includes target "Foo" which requires target "absl::string" that is not in the export set.
```

## CI: Makefile/Docker testing
To test CMake Install rules and build, there is a Makefile in ci folder using
docker containers to test.

To get the help simply type:
```sh
make --directory=ci
```

For example to test the CMake project on ubuntu:
```sh
make --directory=ci test_ubuntu
```

note: to get help you can use
```sh
make --directory=ci
```

## License
Apache 2. See the LICENSE file for details.

## Disclaimer
This is not an official Google product, it is just code that happens to be
owned by Google.
