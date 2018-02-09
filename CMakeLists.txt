cmake_minimum_required(VERSION 3.8.2)

# Set default build type to Release if empty.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
	"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.")

project(meta VERSION 1.0 LANGUAGES NONE)

include(CTest)
include(GNUInstallDirs)

if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries(.so)." ON)
else()
	# only support for static build on Windows.
 set(BUILD_SHARED_LIBS OFF)
endif()

# Build Dependencies
add_subdirectory(cmake)

add_subdirectory(Foo)
add_subdirectory(FooApp)

# Install
install(EXPORT CMakeAbseilTargets
	NAMESPACE CMakeAbseil::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CMakeAbseil
	COMPONENT Devel)
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/CMakeAbseilConfig.cmake.in
	"${PROJECT_BINARY_DIR}/CMakeAbseilConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeAbseil"
	NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/CMakeAbseilConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
	"${PROJECT_BINARY_DIR}/CMakeAbseilConfig.cmake"
	"${PROJECT_BINARY_DIR}/CMakeAbseilConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeAbseil"
	COMPONENT Devel)
