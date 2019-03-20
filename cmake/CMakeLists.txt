set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS OFF)
set(BUILD_TESTING OFF)

##############
##  ABSEIL  ##
##############
message(STATUS "Subproject: ABSEIL...")
# Download and unpack abseil at configure time
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/abseil.CMakeLists.txt
	${CMAKE_BINARY_DIR}/abseil-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-download)
if(result)
  message(FATAL_ERROR "CMake step for abseil failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/abseil-download)
if(result)
  message(FATAL_ERROR "Build step for abseil failed: ${result}")
endif()

add_subdirectory(
	${CMAKE_BINARY_DIR}/abseil-src
	${CMAKE_BINARY_DIR}/abseil-build)
message(STATUS "Subproject: ABSEIL...DONE")
