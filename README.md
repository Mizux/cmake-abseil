[![Build Status](https://travis-ci.org/Mizux/cmake-abseil.svg?branch=master)](https://travis-ci.org/Mizux/cmake-abseil)
[![Build status](https://ci.appveyor.com/api/projects/status/fxxmf49bkboftmg5/branch/master?svg=true)](https://ci.appveyor.com/project/Mizux/cmake-abseil/branch/master)

# Introduction
This is an integration test of Abseil in a Modern [CMake](https://cmake.org/) C++ Project using
 [ExternalProject](https://cmake.org/cmake/help/latest/module/ExternalProject.html) module.

This project should run on Linux, Mac and Windows.

# CMake Dependencies Tree
This CMake project is composed of one executable (FooApp) and one library (Foo)
with the following dependencies:  
```
CCTZ:
Abseil: CCTZ
Foo: Abseil
FooApp: Abseil
```

## Project directory layout
Thus the project layout is as follow:
```
 CMakeLists.txt // meta CMake doing the orchestration.
 cmake
 ├── CMakeLists.txt
 ├── abseil.CMakeLists.txt
 ├── cctz.CMakeLists.txt
 patches
 ├── abseil.patch
 ├── cctz.patch
 Foo
 ├── CMakeLists.txt
 ├── main.cpp
 FooApp
 ├── CMakeLists.txt
 └── src
     └── main.cpp
```

# C++ Project Build
To build the C++ project, as usual:
```sh
cmake -H. -Bbuild -DCMAKE_VERBOSE_MAKEFILE=ON
cmake --build build
```

# Docker testing
To test CMake Install rules and build, there is a Makefile in cmake folder using
docker to test.

For example to test the Cmake project on ubuntu:
```sh
make -f cmake/Makefile test_install_ubuntu
```

note: to get help you can use
```sh
make -f cmake/Makefile help
```

# Known issues

## Alpine Issue
Abseil seems not working on alpine:
```sh
make -f cmake/Makefile build_alpine
```

you'll get the error
```sh
[ 28%] Building CXX object abseil-build/absl/base/CMakeFiles/absl_base.dir/internal/malloc_hook.cc.o
In file included from /project/cache/alpine/abseil-src/absl/base/internal/malloc_hook.cc:542:0:
/project/cache/alpine/abseil-src/absl/base/internal/malloc_hook_mmap_linux.inc: In function 'void* mmap(void*, size_t, int, int, int, off_t)':
/project/cache/alpine/abseil-src/absl/base/internal/malloc_hook_mmap_linux.inc:160:18: error: redefinition of 'void* mmap(void*, size_t, int, int, int, off_t)'
 extern "C" void* mmap(void *start, size_t length, int prot, int flags,
                  ^~~~
In file included from /project/cache/alpine/abseil-src/absl/base/internal/malloc_hook.cc:23:0:
/project/cache/alpine/abseil-src/absl/base/internal/malloc_hook_mmap_linux.inc:144:18: note: 'void* mmap(void*, size_t, int, int, int, off_t)' previously defined here
 extern "C" void* mmap64(void *start, size_t length, int prot, int flags,
                  ^
make[2]: *** [abseil-build/absl/base/CMakeFiles/absl_base.dir/build.make:231: abseil-build/absl/base/CMakeFiles/absl_base.dir/internal/malloc_hook.cc.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:1544: abseil-build/absl/base/CMakeFiles/absl_base.dir/all] Error 2
```

## Windows Visual Studio Issue

While Foo depends on abseil as private, CMake still complains to not find it in the export rules.<br>
i.e. you can't create library which depends on abseil (even in static internaly).<br>
cf. https://ci.appveyor.com/project/Mizux/cmake-abseil/build/2/job/g0ir3icxywa9jhkk#L188

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
