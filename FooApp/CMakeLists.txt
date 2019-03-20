project(FooApp VERSION 1.0.0 LANGUAGES CXX)

file(GLOB _SRCS "src/*.[hc]pp")

if(TARGET absl::base)
	message(STATUS "Found Target: absl::base")
else()
	message(FATAL_ERROR "Target absl::base not found")
endif()

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE ${_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
#target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_11)
set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED ON
  VERSION ${PROJECT_VERSION})
target_link_libraries(${PROJECT_NAME} PUBLIC absl::base absl::time)
add_executable(CMakeAbseil::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Test
include(CTest)
if(BUILD_TESTING)
	add_test(NAME FooApp_UT COMMAND FooApp)
endif()

# Install
install(TARGETS	${PROJECT_NAME}
	EXPORT CMakeAbseilTargets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
