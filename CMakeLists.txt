cmake_minimum_required(VERSION 3.1.0)

# set build type
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

# include specific functions
include("${CMAKE_SOURCE_DIR}/CMakeFuncs.cmake")

# set global variables
set(PROJECT_CPP_STANDART "cxx_std_17")
set(PROJECT_NAME "GB")
set(LIB_NAME "GBLib")

set(LIST_AVALIBLE_EXTENSIONS ".h" ".hpp" ".cpp")

# set project name
project(${PROJECT_NAME})

# set include directories
include_directories("${CMAKE_SOURCE_DIR}/")

# find all source files for this project
set(listAvalibleFilesTemplates ".+\\.h" ".+\\.hpp" ".+\\.cpp")
set(listIngnoredDirectoryes "${CMAKE_SOURCE_DIR}/tests" "${CMAKE_SOURCE_DIR}/build" "${CMAKE_SOURCE_DIR}/.git")
FindAllSourceFiles("Find all files for the ${LIB_NAME}.lib" "${CMAKE_CURRENT_SOURCE_DIR}" "${listIngnoredDirectoryes}" "${listAvalibleFilesTemplates}" listTargetSourceFiles)

# compose all founded source files by directory
ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetSourceFiles}")

# create library
add_library(${LIB_NAME} STATIC "${listTargetSourceFiles}")
target_compile_features(${LIB_NAME} PRIVATE ${PROJECT_CPP_STANDART})

# add tests
add_subdirectory(./tests)
