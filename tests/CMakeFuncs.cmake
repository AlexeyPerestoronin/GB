include("${CMAKE_SOURCE_DIR}/CMakeFuncs.cmake")

# brief: add Google tests to current test-project
# note1: the google tests project downloads from its git-repository and builds before building the test-protect
# note2: if google tests has been download and build early it not be do again
function(AddGoogleTests)
    if(TARGET GTest::gtest_main AND TARGET GTest::gmock_main)
        message(INFO "GTest and GMock is already downloaded, build and loaded")
        return()
    endif()

    # this technique from: https://crascit.com/2015/07/25/cmake-gtest/
    configure_file(CMakeLists.txt.in ${CMAKE_BINARY_DIR}/tests/googletest-download/CMakeLists.txt)

    execute_process(
        COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
    )
    execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/tests/googletest-download"
    )

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds the following targets:
    # gtest, gtest_main, gmock and gmock_main
    add_subdirectory(
        ${CMAKE_BINARY_DIR}/tests/googletest-src
        ${CMAKE_BINARY_DIR}/tests/googletest-build
    )

    # The gtest/gmock targets carry header search path dependencies
    # automatically when using CMake 2.8.11 or later. Otherwise we
    # have to add them here ourselves.
    if(CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include"
                            "${gmock_SOURCE_DIR}/include"
        )
    endif()
endfunction(AddGoogleTests)


# brief: creates unit tests as one test project
function(AddUnitTests)
    # find all source files for unit-tests
    set(listAvalibleFilesTemplates "test-unit.+\\.h" "test-unit.+\\.hpp" "test-unit-.+\\.cpp")
    FindAllSourceFiles("Find all files for unit-tests" "${CMAKE_CURRENT_SOURCE_DIR}" "" "${listAvalibleFilesTemplates}" listTargetSourceUnitTestsFiles)

    # find all base files for tests
    set(listAvalibleFilesTemplates "test-common.hpp" "test-main.cpp")
    FindAllSourceFiles("Find base files for tests" "${CMAKE_CURRENT_SOURCE_DIR}" "" "${listAvalibleFilesTemplates}" listTargetTestsFiles)

    # compose all founded files by directory
    ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetSourceUnitTestsFiles}")
    ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetTestsFiles}")

    add_executable(${UNIT_TESTS_EXE_NAME} ${listTargetSourceUnitTestsFiles} ${listTargetTestsFiles})
    target_compile_features(${UNIT_TESTS_EXE_NAME} PRIVATE ${PROJECT_CPP_STANDART})
    target_link_libraries(${UNIT_TESTS_EXE_NAME} GTest::gtest_main)
    target_link_libraries(${UNIT_TESTS_EXE_NAME} GTest::gmock_main)
    target_link_libraries(${UNIT_TESTS_EXE_NAME} ${LIB_NAME})
endfunction(AddUnitTests)


# brief: creates suit tests
# note1: one suit test is creates from one code file and presents as unique project
function(AddSuitTests)
    # find all source files for suit-tests
    set(listAvalibleFilesTemplates "test-suit.+\\.h" "test-suit.+\\.hpp" "test-suit-.+\\.cpp")
    FindAllSourceFiles("Find all files for suit-tests" "${CMAKE_CURRENT_SOURCE_DIR}" "" "${listAvalibleFilesTemplates}" listTargetSourceSuitTestsFiles)

    # find all base files for tests
    set(listAvalibleFilesTemplates "test-common.hpp" "test-main.cpp")
    FindAllSourceFiles("Find base files for tests" "${CMAKE_CURRENT_SOURCE_DIR}" "" "${listAvalibleFilesTemplates}" listTargetTestsFiles)

    # compose all founded files by directory
    ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetSourceSuitTestsFiles}")
    ComposeFileBySourceGroup("${CMAKE_CURRENT_SOURCE_DIR}" "${listTargetTestsFiles}")

    foreach(oneSuitTestFile ${listTargetSourceSuitTestsFiles})
        get_filename_component(suitTestFileName ${oneSuitTestFile} NAME_WE)
        set(suitTestExeName ${LIB_NAME}-${suitTestFileName})
        add_executable(${suitTestExeName} ${oneSuitTestFile} ${listTargetTestsFiles})
        target_compile_features(${suitTestExeName} PRIVATE ${PROJECT_CPP_STANDART})
        target_link_libraries(${suitTestExeName} GTest::gtest_main)
        target_link_libraries(${suitTestExeName} GTest::gmock_main)
        target_link_libraries(${suitTestExeName} ${LIB_NAME})
    endforeach()
endfunction(AddSuitTests)
