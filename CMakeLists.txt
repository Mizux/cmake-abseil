cmake_minimum_required(VERSION 3.5)

if(POLICY CMP0022)
	cmake_policy(SET CMP0022 NEW)
endif()

project(CMakeAbseil VERSION 1.0)

include(CTest)
include(GNUInstallDirs)

# Set default build type to Release if empty.
set(CMAKE_BUILD_TYPE "Release" CACHE STRING
	"Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel.")

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
install(EXPORT ${PROJECT_NAME}Targets
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/CMakeAbseil"
	NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	COMPATIBILITY SameMajorVersion)
install(
	FILES
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
