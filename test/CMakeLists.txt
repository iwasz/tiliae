CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

ENABLE_TESTING ()

INCLUDE_DIRECTORIES ("../src")
INCLUDE_DIRECTORIES (./ /usr/include/libcxxabi)
ADD_DEFINITIONS (-Wall)

#SET (CMAKE_C_FLAGS "-ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART ")
#SET (CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART -std=c++11 -stdlib=libc++")
#SET (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-gc-sections")
#SET (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-undefined,-gc-sections")

SET (CMAKE_CXX_FLAGS "-DALLOW_CAST_TO_SMART -std=c++11")
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET (CMAKE_VERBOSE_MAKEFILE OFF)

find_package (Boost REQUIRED COMPONENTS system prg_exec_monitor unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})
#MESSAGE ("---> ${Boost_INCLUDE_DIRS}")
#MESSAGE ("---> ${Boost_LIBRARY_DIRS}")
#MESSAGE ("---> ${Boost_LIBRARIES}")

IF (WITH_ANNOTATIONS)
        MESSAGE (STATUS "Building reflection with annotations.")
        ADD_DEFINITIONS (-DWITH_ANNOTATIONS)
ENDIF ()

IF (WITH_PARSER)
        MESSAGE (STATUS "Building reflection with parser.")
        ADD_DEFINITIONS (-DWITH_PARSER)
ENDIF ()

## --------------------------------------------------------
## Testy.
## --------------------------------------------------------
IF (BUILD_TEST_HELPERS AND BUILD_TESTS)
        SET(SOURCES)

        IF (WITH_PARSER)
                TILIAE_PARSE ("${CMAKE_BINARY_DIR}/parser/tiliaeparser" "testHelpers" "testHelpers/Reflection_input.cc" "testHelpers/Reflection_output.cc.h")
                LIST (APPEND SOURCES "testHelpers/Reflection_input.cc")
                LIST (APPEND SOURCES "testHelpers/Reflection_output.cc.h")
        ENDIF ()

        AUX_SOURCE_DIRECTORY (testHelpers SOURCES)
        ADD_LIBRARY (testHelpers STATIC ${SOURCES})
        TARGET_LINK_LIBRARIES (testHelpers tiliae)

IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (testHelpers c++abi)
ENDIF ()
ENDIF ()

IF(BUILD_CORE AND BUILD_TESTS)

    SET(SOURCES)
    AUX_SOURCE_DIRECTORY (core SOURCES)
    add_executable (core_test ${SOURCES})
#    SET_TARGET_PROPERTIES (core_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)

IF (WITH_CPPABI)
    TARGET_LINK_LIBRARIES (core_test c++abi)
ENDIF()
    TARGET_LINK_LIBRARIES (core_test ${Boost_LIBRARIES})
    TARGET_LINK_LIBRARIES (core_test tiliae)

    ADD_TEST (core_test core_test)

    #To jest programik do optymalizacji pod kątem wielkości binarek
    IF (0)
        SET(SOURCES)
        AUX_SOURCE_DIRECTORY (core/testSize SOURCES)
        add_executable (sizeLight ${SOURCES})
        TARGET_LINK_LIBRARIES (sizeLight tiliaecore)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (sizeLight c++abi)
ENDIF()
    ENDIF()

ENDIF()
## --------------------------------------------------------
IF(BUILD_COMMON AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (common TEST_SOURCES)
        add_executable (common_test ${TEST_SOURCES})

IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (common_test c++abi)
ENDIF()
        TARGET_LINK_LIBRARIES (common_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (common_test tiliae)

        ADD_TEST (common_test common_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_REFLECTION AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (reflection TEST_SOURCES)

        add_executable (reflection_test ${TEST_SOURCES})
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (reflection_test c++abi)
ENDIF()
        TARGET_LINK_LIBRARIES (reflection_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (reflection_test tiliae)
        TARGET_LINK_LIBRARIES (reflection_test testHelpers)

        ADD_TEST (reflection_test reflection_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (beanWrapper TEST_SOURCES)
        ADD_EXECUTABLE (bwrap_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (bwrap_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (bwrap_test tiliae)
        TARGET_LINK_LIBRARIES (bwrap_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (bwrap_test c++abi)
ENDIF()
        ADD_TEST (bwrap_test bwrap_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_FACTORY AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (factory TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (factory/testHelpers TEST_SOURCES)

        add_executable (factory_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (factory_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (factory_test tiliae)
        TARGET_LINK_LIBRARIES (factory_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (factory_test c++abi)
ENDIF()

        ADD_TEST (factory_test factory_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_EDITOR AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (editor TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (editor/testHelpers TEST_SOURCES)
        add_executable (editor_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (editor_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (editor_test tiliae)
        TARGET_LINK_LIBRARIES (editor_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (editor_test c++abi)
ENDIF()
        ADD_TEST (editor_test editor_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_K202 AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (k202 TEST_SOURCES)
        add_executable (k202_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (k202_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (k202_test tiliae)
        TARGET_LINK_LIBRARIES (k202_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (k202_test c++abi)
ENDIF()
        ADD_TEST (k202_test k202_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_SIGNAL AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (signal TEST_SOURCES)
        add_executable (signal_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (signal_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (signal_test tiliae)
        TARGET_LINK_LIBRARIES (signal_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (signal_test c++abi)
ENDIF()

        ADD_TEST (signal_test signal_test)
ENDIF()
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE AND BUILD_TESTS)
        SET (TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (stateMachine TEST_SOURCES)
        add_executable (machine_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (machine_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (machine_test tiliae)
        TARGET_LINK_LIBRARIES (machine_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (machine_test c++abi)
ENDIF()

        ADD_TEST (machine_test machine_test)
ENDIF()
## container test -----------------------------------------
IF(BUILD_CONTAINER AND BUILD_TESTS)
        SET(TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/beanFactory TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/common TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/testHelpers TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/inputFormat/mxml TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/inputFormat/compact TEST_SOURCES)
        AUX_SOURCE_DIRECTORY (container/metaStructure TEST_SOURCES)

        add_executable (container_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (container_test ${Boost_LIBRARIES})
        TARGET_LINK_LIBRARIES (container_test tiliae)
        TARGET_LINK_LIBRARIES (container_test testHelpers)
IF (WITH_CPPABI)
        TARGET_LINK_LIBRARIES (container_test c++abi)
ENDIF()
		
        ADD_TEST (container_test container_test)
ENDIF()

## DEMO ---------------------------------------------------

IF(BUILD_DEMO)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../demo/ DEMO_SOURCES)

    add_executable (demo ${DEMO_SOURCES})
#    SET_TARGET_PROPERTIES (demo PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (demo boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (demo tiliae)

ENDIF ()
