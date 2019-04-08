set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)

##############
##  ABSEIL  ##
##############
message(STATUS "Building: ABSEIL...")

# Download, build, install abseil-cpp at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/abseil.CMakeLists.txt
	${CMAKE_BINARY_DIR}/abseil-cpp/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -H. -Bproject_build -G "${CMAKE_GENERATOR}"
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-cpp)
if(result)
  message(FATAL_ERROR "CMake step for abseil failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build project_build --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-cpp)
if(result)
  message(FATAL_ERROR "Build step for abseil failed: ${result}")
endif()

message(STATUS "Building: ABSEIL...DONE")
