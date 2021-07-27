cmake_minimum_required(VERSION 3.1.0)

# include specific functions
include("${CMAKE_CURRENT_SOURCE_DIR}/CMakeFuncs.cmake")

# set global variables
set(UNIT_TESTS_EXE_NAME ${LIB_NAME}-unit-tests)

# set name for unit-test-project(s)
project(${UNIT_TESTS_EXE_NAME} NONE)

# set include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/")
include_directories("${CMAKE_SOURCE_DIR}/")

# add google-test framework inside project
AddGoogleTests()
# add unit tests
AddUnitTests()
# add suit tests
AddSuitTests()
