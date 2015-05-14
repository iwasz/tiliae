CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
project (tiliae)

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Here we can set what to build actually (1=build, 0=do not build).
SET (BUILD_CORE                ON CACHE BOOL "")
SET (BUILD_COMMON              ON CACHE BOOL "")
SET (BUILD_REFLECTION          ON CACHE BOOL "")
SET (BUILD_TEST_HELPERS        ON CACHE BOOL "") # Buduje tylko gdy BUILD_TESTS true
SET (BUILD_FACTORY             ON CACHE BOOL "")
SET (BUILD_EDITOR              ON CACHE BOOL "")
SET (BUILD_BEAN_WRAPPER        ON CACHE BOOL "")
SET (BUILD_K202                ON CACHE BOOL "")
SET (BUILD_SIGNAL              ON CACHE BOOL "")
SET (BUILD_STATE_MACHINE       OFF CACHE BOOL "")
SET (BUILD_CONTAINER           ON CACHE BOOL "")
SET (BUILD_DEMO                ON CACHE BOOL "")
SET (BUILD_TESTS               ON CACHE BOOL "")
SET (WITH_CORE_STRING          OFF CACHE BOOL "")

if (WITH_CORE_STRING)
    add_definitions (-DWITH_CORE_STRING)
endif ()

if (ANDROID)
    SET (BUILD_DEMO                0)
    SET (BUILD_TESTS               0)
endif()    

if (WITH_CORE_STRING)
    add_definitions (-DWITH_CORE_STRING)
endif ()

#SET (TARGET_PLATFORM "" CACHE STRING "Na jaka platforme budujemy") 
#SET_PROPERTY (CACHE TARGET_PLATFORM PROPERTY STRINGS Linux Windows Android iPhone)

SET (CMAKE_C_FLAGS "-fvisibility=hidden -DTILIAE_DLL -ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART ")
SET (CMAKE_CXX_FLAGS "-fvisibility=hidden -DTILIAE_DLL -ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART -std=c++11 ")
SET (CMAKE_C_FLAGS_RELEASE "-fvisibility=hidden -DTILIAE_DLL -ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE "-fvisibility=hidden -DTILIAE_DLL -ffunction-sections -fdata-sections -DALLOW_CAST_TO_SMART -DNDEBUG -std=c++11 ")
#ADD_DEFINITIONS (-Wall)

SET (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
SET (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-undefined")
SET (CMAKE_VERBOSE_MAKEFILE 1)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/../src/"
    DESTINATION "include/tiliae" 
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/pc/"
    DESTINATION "lib/pkgconfig"
    FILES_MATCHING PATTERN "*.pc"
    PATTERN "*.svn*" EXCLUDE)

if (NOT ANDROID)
    SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
    SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
endif()

find_package (Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include (FindPkgConfig)
pkg_check_modules (MXML REQUIRED "mxml")
INCLUDE_DIRECTORIES (${MXML_INCLUDE_DIRS})
link_directories(${MXML_LIBRARY_DIRS})


FIND_PATH (SPARSEHASH_INCLUDE_DIR "google/sparse_hash_map")

IF (NOT SPARSEHASH_INCLUDE_DIR)
    MESSAGE (FATAL_ERROR "libsparsehash not found.")
ELSE ()
    INCLUDE_DIRECTORIES (${SPARSEHASH_INCLUDE_DIR})
ENDIF ()

ENABLE_TESTING ()

INCLUDE_DIRECTORIES (../src)

## --------------------------------------------------------
## Core
## --------------------------------------------------------
IF(BUILD_CORE)
    ADD_DEFINITIONS (-DBUILD_CORE)
    AUX_SOURCE_DIRECTORY (../src/core LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/variant LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/string LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/allocator LIB_SOURCES)      
ENDIF(BUILD_CORE)
## --------------------------------------------------------
## TestHelpers
## --------------------------------------------------------
IF(BUILD_TEST_HELPERS AND BUILD_TESTS)
    ADD_DEFINITIONS (-DBUILD_TEST_HELPERS)
    AUX_SOURCE_DIRECTORY (../src/testHelpers LIB_SOURCES)
ENDIF()
## --------------------------------------------------------
## Common
## --------------------------------------------------------
IF(BUILD_COMMON)
    ADD_DEFINITIONS (-DBUILD_COMMON)
    AUX_SOURCE_DIRECTORY (../src/common/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/logger LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/path LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/collection LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/dataSource LIB_SOURCES)
ENDIF(BUILD_COMMON)
## --------------------------------------------------------
## Reflection
## --------------------------------------------------------
IF(BUILD_REFLECTION)
    ADD_DEFINITIONS (-DBUILD_REFLECTION)
    AUX_SOURCE_DIRECTORY (../src/reflection/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/wrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/annotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/visitor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/reflectAnnotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/model LIB_SOURCES)
ENDIF(BUILD_REFLECTION)
## --------------------------------------------------------
## BeanWrapper
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER)
    ADD_DEFINITIONS (-DBUILD_BEAN_WRAPPER)    
    AUX_SOURCE_DIRECTORY (../src/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/plugins LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/misc LIB_SOURCES)
ENDIF(BUILD_BEAN_WRAPPER)
## --------------------------------------------------------
## Factory
## --------------------------------------------------------
IF(BUILD_FACTORY)
    ADD_DEFINITIONS (-DBUILD_FACTORY)
    AUX_SOURCE_DIRECTORY (../src/factory LIB_SOURCES)   
ENDIF(BUILD_FACTORY)
## --------------------------------------------------------
## Editor
## --------------------------------------------------------
IF(BUILD_EDITOR)
    ADD_DEFINITIONS (-DBUILD_EDITOR)    
    AUX_SOURCE_DIRECTORY (../src/editor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/scalar LIB_SOURCES)
ENDIF(BUILD_EDITOR)
## --------------------------------------------------------
## K202 expression script
## --------------------------------------------------------
IF(BUILD_K202)
    ADD_DEFINITIONS (-DBUILD_K202)        
    AUX_SOURCE_DIRECTORY (../src/k202 LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/compiler LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/expression LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/misc LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/extension LIB_SOURCES)
ENDIF(BUILD_K202)
## --------------------------------------------------------
## Signal                  
## --------------------------------------------------------
IF(BUILD_SIGNAL)
    ADD_DEFINITIONS (-DBUILD_SIGNAL)        
    AUX_SOURCE_DIRECTORY (../src/signal LIB_SOURCES)
ENDIF(BUILD_SIGNAL)
## --------------------------------------------------------
## StateMachine
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE)
    ADD_DEFINITIONS (-DBUILD_STATE_MACHINE)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/condition LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/extension LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/input LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/output LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/action LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/context LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/transition LIB_SOURCES)
ENDIF(BUILD_STATE_MACHINE)
## --------------------------------------------------------
## container
## --------------------------------------------------------
IF(BUILD_CONTAINER)
    ADD_DEFINITIONS (-DBUILD_CONTAINER)
    AUX_SOURCE_DIRECTORY (../src/container LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/factory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/service LIB_SOURCES)
       
    AUX_SOURCE_DIRECTORY (../src/container/common LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/id LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (../src/container/inputFormat LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/mxml/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/compact/ LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (../src/container/metaStructure LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/service LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/data LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/elem LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/meta LIB_SOURCES)
ENDIF(BUILD_CONTAINER)

## --------------------------------------------------------
## Biblioteka Tiliae - all in one.
## --------------------------------------------------------

if (ANDROID)
    add_library (tiliae STATIC ${LIB_SOURCES})
else ()
    add_library (tiliae SHARED ${LIB_SOURCES})
    TARGET_LINK_LIBRARIES (tiliae ${MXML_LIBRARIES})
endif ()

INSTALL (
    TARGETS tiliae
    DESTINATION lib 
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

## --------------------------------------------------------
## Testy.
## --------------------------------------------------------
#ADD_DEFINITIONS (-DREFLECTION_ENABLED)

IF(BUILD_CORE AND BUILD_TESTS)

    SET(SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/test SOURCES)
    add_executable (core_test ${SOURCES})
    SET_TARGET_PROPERTIES (core_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    
    TARGET_LINK_LIBRARIES (core_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (core_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (core_test tiliae)

    ADD_TEST (core_test core_test)
    
    #To jest programik do optymalizacji pod kątem wielkości binarek
    IF (0)
        SET(SOURCES)
        AUX_SOURCE_DIRECTORY (../src/core/test/testSize SOURCES)
        add_executable (sizeLight ${SOURCES})
        TARGET_LINK_LIBRARIES (sizeLight tiliaecore)
    ENDIF()
    
ENDIF()
## --------------------------------------------------------
IF(BUILD_COMMON AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/test TEST_SOURCES)   
    add_executable (common_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (common_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    
    TARGET_LINK_LIBRARIES (common_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (common_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (common_test tiliae)

    ADD_TEST (common_test common_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_REFLECTION AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/test/testHelpers TEST_SOURCES)

    add_executable (reflection_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (reflection_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (reflection_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (reflection_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (reflection_test tiliae)

    ADD_TEST (reflection_test reflection_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_TOOLS AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/tools/test TEST_SOURCES)

    add_executable (tools_test ${TEST_SOURCES})  
    SET_TARGET_PROPERTIES (tools_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (tools_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (tools_test tiliae)

    ADD_TEST (tools_test tools_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/test TEST_SOURCES)

    add_executable (bwrap_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (bwrap_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (bwrap_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (bwrap_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (bwrap_test tiliae)

    ADD_TEST (bwrap_test bwrap_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_FACTORY AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/factory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/factory/testHelpers TEST_SOURCES)
    
    add_executable (factory_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (factory_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (factory_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (factory_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (factory_test tiliae)

    ADD_TEST (factory_test factory_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_EDITOR AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/testHelpers TEST_SOURCES)

    add_executable (editor_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (editor_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (editor_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (editor_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (editor_test tiliae)

    ADD_TEST (editor_test editor_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_K202 AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/test TEST_SOURCES)

    add_executable (k202_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (k202_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (k202_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (k202_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (k202_test tiliae)

    ADD_TEST (k202_test k202_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_SIGNAL AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/signal/test TEST_SOURCES)

    add_executable (signal_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (signal_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (signal_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (signal_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (signal_test tiliae)

    ADD_TEST (signal_test signal_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/test TEST_SOURCES)

    add_executable (machine_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (machine_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (machine_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (machine_test boost_prg_exec_monitor)    
    TARGET_LINK_LIBRARIES (machine_test tiliae)

    ADD_TEST (machine_test machine_test)

ENDIF()
## container test -----------------------------------------
IF(BUILD_CONTAINER AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/testHelpers TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/mxml/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/compact/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/testHelpers TEST_SOURCES)
     
    add_executable (container_test ${TEST_SOURCES})
    SET_TARGET_PROPERTIES (container_test PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (container_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (container_test tiliae)

    ADD_TEST (container_test container_test)

ENDIF()

## DEMO ---------------------------------------------------

IF(BUILD_DEMO)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../demo/ DEMO_SOURCES)
         
    add_executable (demo ${DEMO_SOURCES})
    SET_TARGET_PROPERTIES (demo PROPERTIES COMPILE_FLAGS -DREFLECTION_ENABLED)
    TARGET_LINK_LIBRARIES (demo boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (demo tiliae)

ENDIF ()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/pc/tiliae.pc.in ${CMAKE_CURRENT_BINARY_DIR}/pc/tiliae.pc @ONLY)
