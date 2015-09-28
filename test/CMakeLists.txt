CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

ENABLE_TESTING ()

INCLUDE_DIRECTORIES ("../src")
INCLUDE_DIRECTORIES ("./")
ADD_DEFINITIONS (-Wall)

#SET (CMAKE_C_FLAGS "-ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART ")
#SET (CMAKE_CXX_FLAGS "-ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART -std=c++11 -stdlib=libc++")
#SET (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined,-gc-sections")
#SET (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-undefined,-gc-sections")

SET (CMAKE_CXX_FLAGS "-DALLOW_CAST_TO_SMART -std=c++11 -stdlib=libc++")
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)

## --------------------------------------------------------
## Testy.
## --------------------------------------------------------
IF (BUILD_TEST_HELPERS AND BUILD_TESTS)
        SET(SOURCES)

        IF (WITH_PARSER)
                TILIAE_PARSE ("${CMAKE_BINARY_DIR}/parser/tiliaeparser" "testHelpers/Reflection.cc" PARSER_OUTPUT_FILE)
                LIST (APPEND SOURCES ${PARSER_OUTPUT_FILE})
                LIST (APPEND SOURCES "testHelpers/Reflection.cc")
        ENDIF ()

        AUX_SOURCE_DIRECTORY (testHelpers SOURCES)
        ADD_LIBRARY (testHelpers ${SOURCES})
        TARGET_LINK_LIBRARIES (testHelpers c++abi)
ENDIF ()

IF(BUILD_CORE AND BUILD_TESTS)

    SET(SOURCES)
    AUX_SOURCE_DIRECTORY (core SOURCES)
    add_executable (core_test ${SOURCES})
#    SET_TARGET_PROPERTIES (core_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)

    TARGET_LINK_LIBRARIES (core_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (core_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (core_test tiliae)
    TARGET_LINK_LIBRARIES (core_test c++abi)

    ADD_TEST (core_test core_test)

    #To jest programik do optymalizacji pod kątem wielkości binarek
    IF (0)
        SET(SOURCES)
        AUX_SOURCE_DIRECTORY (core/testSize SOURCES)
        add_executable (sizeLight ${SOURCES})
        TARGET_LINK_LIBRARIES (sizeLight tiliaecore)
        TARGET_LINK_LIBRARIES (sizeLight c++abi)
    ENDIF()

ENDIF()
## --------------------------------------------------------
IF(BUILD_COMMON AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (common TEST_SOURCES)
    add_executable (common_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (common_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)

    TARGET_LINK_LIBRARIES (common_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (common_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (common_test tiliae)
    TARGET_LINK_LIBRARIES (common_test c++abi)

    ADD_TEST (common_test common_test)

ENDIF()

IF (0)
## --------------------------------------------------------
IF(BUILD_REFLECTION AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/testHelpers TEST_SOURCES)

    add_executable (reflection_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (reflection_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (reflection_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (reflection_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (reflection_test tiliae)
    TARGET_LINK_LIBRARIES (reflection_test testHelpers)
    TARGET_LINK_LIBRARIES (reflection_test c++abi)

    ADD_TEST (reflection_test reflection_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_TOOLS AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (tools/test TEST_SOURCES)

    add_executable (tools_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (tools_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (tools_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (tools_test tiliae)
    TARGET_LINK_LIBRARIES (tools_test c++abi)

    ADD_TEST (tools_test tools_test)

ENDIF()
endif ()
## --------------------------------------------------------

IF(BUILD_BEAN_WRAPPER AND BUILD_TESTS)
        SET(TEST_SOURCES)

        IF (WITH_PARSER)
                TILIAE_PARSE ("${CMAKE_BINARY_DIR}/parser/tiliaeparser" "beanWrapper/Reflection.cc" PARSER_OUTPUT_FILE)
                LIST (APPEND TEST_SOURCES ${PARSER_OUTPUT_FILE})
                LIST (APPEND TEST_SOURCES "beanWrapper/Reflection.cc")
        ENDIF ()

        AUX_SOURCE_DIRECTORY (beanWrapper TEST_SOURCES)

        ADD_EXECUTABLE (bwrap_test ${TEST_SOURCES})
        TARGET_LINK_LIBRARIES (bwrap_test boost_unit_test_framework)
        TARGET_LINK_LIBRARIES (bwrap_test boost_prg_exec_monitor)
        TARGET_LINK_LIBRARIES (bwrap_test tiliae)
        TARGET_LINK_LIBRARIES (bwrap_test testHelpers)
        TARGET_LINK_LIBRARIES (bwrap_test c++abi)

        ADD_TEST (bwrap_test bwrap_test)
ENDIF()
## --------------------------------------------------------
if (0)
IF(BUILD_FACTORY AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (factory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (factory/testHelpers TEST_SOURCES)

    add_executable (factory_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (factory_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (factory_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (factory_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (factory_test tiliae)

    ADD_TEST (factory_test factory_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_EDITOR AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (editor/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (editor/testHelpers TEST_SOURCES)

    add_executable (editor_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (editor_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (editor_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (editor_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (editor_test tiliae)

    ADD_TEST (editor_test editor_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_K202 AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (k202/test TEST_SOURCES)

    add_executable (k202_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (k202_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (k202_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (k202_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (k202_test tiliae)

    ADD_TEST (k202_test k202_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_SIGNAL AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (signal/test TEST_SOURCES)

    add_executable (signal_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (signal_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (signal_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (signal_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (signal_test tiliae)

    ADD_TEST (signal_test signal_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/test TEST_SOURCES)

    add_executable (machine_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (machine_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (machine_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (machine_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (machine_test tiliae)

    ADD_TEST (machine_test machine_test)

ENDIF()
## container test -----------------------------------------
IF(BUILD_CONTAINER AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/beanFactory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/common/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/common/testHelpers TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/inputFormat/mxml/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/inputFormat/compact/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (editor/testHelpers TEST_SOURCES)

    add_executable (container_test ${TEST_SOURCES})
#    SET_TARGET_PROPERTIES (container_test PROPERTIES COMPILE_FLAGS -DWITH_ANNOTATIONS)
    TARGET_LINK_LIBRARIES (container_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (container_test tiliae)

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

ENDIF ()
