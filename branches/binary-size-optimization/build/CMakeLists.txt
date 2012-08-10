CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

project (tiliae)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Here we can set what to build actually (1=build, 0=do not build).
SET (BUILD_CORE                1)
SET (BUILD_COMMON              1)
SET (BUILD_REFLECTION          1)
SET (BUILD_TEST_HELPERS        1) # Buduje tylko gdy BUILD_TESTS true
SET (BUILD_FACTORY             1)
SET (BUILD_EDITOR              1)
SET (BUILD_BEAN_WRAPPER        1)
SET (BUILD_K202                0)
SET (BUILD_SIGNAL              0)
SET (BUILD_STATE_MACHINE       0)
SET (BUILD_CONTAINER           1)
SET (BUILD_DEMO                1)
SET (BUILD_TESTS               1)

#SET (TARGET_PLATFORM "" CACHE STRING "Na jaka platforme budujemy") 
#SET_PROPERTY (CACHE TARGET_PLATFORM PROPERTY STRINGS Linux Windows Android iPhone)

SET (CMAKE_VERBOSE_MAKEFILE 0) 
ADD_DEFINITIONS (-g -fvisibility=hidden -DTILIAE_DLL -Wall)
#ADD_DEFINITIONS (-DNDEBUG)
ADD_DEFINITIONS (-O0)
ADD_DEFINITIONS (-ffunction-sections -fdata-sections)
#ADD_DEFINITIONS (-DALLOW_CAST_TO_SMART)

SET (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
SET (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-undefined")

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

if (UNIX)
    SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local") 
    SET (CMAKE_PREFIX_PATH "/home/iwasz/local")
endif()

SET(Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0")
find_package (Boost 1.41.0)
include_directories(${Boost_INCLUDE_DIRS})

# TODO inaczej!
if (NOT ANDROID)
    include (FindPkgConfig)
    pkg_check_modules (MXML REQUIRED "mxml")
    INCLUDE_DIRECTORIES (${MXML_INCLUDE_DIRS})
    link_directories(${MXML_LIBRARY_DIRS})

    pkg_check_modules (SPARSE_HASH REQUIRED "libsparsehash")
    INCLUDE_DIRECTORIES (${SPARSE_HASH_INCLUDE_DIRS})

else ()
    find_library (MXML_LIBRARIES "mxml")
endif ()


ENABLE_TESTING ()

## --------------------------------------------------------
## Core
## --------------------------------------------------------
IF(BUILD_CORE)

    AUX_SOURCE_DIRECTORY (../src/core LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/variant LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/string LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/allocator LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/core/)
   
ENDIF(BUILD_CORE)
## --------------------------------------------------------
## TestHelpers
## --------------------------------------------------------
IF(BUILD_TEST_HELPERS AND BUILD_TESTS)

    AUX_SOURCE_DIRECTORY (../src/testHelpers LIB_SOURCES)
    INCLUDE_DIRECTORIES (../src/testHelpers)

ENDIF()
## --------------------------------------------------------
## Common
## --------------------------------------------------------
IF(BUILD_COMMON)

    AUX_SOURCE_DIRECTORY (../src/common/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/logger LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/path LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/collection LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/common/)

ENDIF(BUILD_COMMON)
## --------------------------------------------------------
## Reflection
## --------------------------------------------------------
IF(BUILD_REFLECTION)
    
    AUX_SOURCE_DIRECTORY (../src/reflection/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/wrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/annotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/visitor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/reflectAnnotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/model LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/reflection)

ENDIF(BUILD_REFLECTION)
## --------------------------------------------------------
## BeanWrapper
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER)
    
    AUX_SOURCE_DIRECTORY (../src/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/plugins LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/misc LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/beanWrapper) 
    
ENDIF(BUILD_BEAN_WRAPPER)
## --------------------------------------------------------
## Factory
## --------------------------------------------------------
IF(BUILD_FACTORY)
    
    AUX_SOURCE_DIRECTORY (../src/factory LIB_SOURCES)   
    
    INCLUDE_DIRECTORIES (../src/factory)

ENDIF(BUILD_FACTORY)
## --------------------------------------------------------
## Editor
## --------------------------------------------------------
IF(BUILD_EDITOR)
    
    AUX_SOURCE_DIRECTORY (../src/editor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/scalar LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/editor)
    
ENDIF(BUILD_EDITOR)
## --------------------------------------------------------
## K202 expression script
## --------------------------------------------------------
IF(BUILD_K202)
    
    AUX_SOURCE_DIRECTORY (../src/k202 LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/compiler LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/expression LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/misc LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/extension LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/k202/)
    
ENDIF(BUILD_K202)
## --------------------------------------------------------
## Signal                  
## --------------------------------------------------------
IF(BUILD_SIGNAL)
    
    AUX_SOURCE_DIRECTORY (../src/signal LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/signal/)
    
ENDIF(BUILD_SIGNAL)
## --------------------------------------------------------
## StateMachine
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE)
    
    AUX_SOURCE_DIRECTORY (../src/stateMachine/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/condition LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/extension LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/input LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/output LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/action LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/context LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/transition LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/stateMachine)

ENDIF(BUILD_STATE_MACHINE)
## --------------------------------------------------------
## container
## --------------------------------------------------------
IF(BUILD_CONTAINER)

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
  
    INCLUDE_DIRECTORIES (../src/container)
    
ENDIF(BUILD_CONTAINER)

## --------------------------------------------------------
## Biblioteka Tiliae - all in one.
## --------------------------------------------------------

if (ANDROID)
    add_library (tiliae STATIC ${LIB_SOURCES})
else ()
    add_library (tiliae SHARED ${LIB_SOURCES})
endif ()

TARGET_LINK_LIBRARIES (tiliae ${MXML_LIBRARIES})

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
IF(BUILD_CORE AND BUILD_TESTS)

    SET(SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/test SOURCES)
    add_executable (core_test ${SOURCES})
    
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
    TARGET_LINK_LIBRARIES (tools_test boost_prg_exec_monitor)
    TARGET_LINK_LIBRARIES (tools_test tiliae)

    ADD_TEST (tools_test tools_test)

ENDIF()
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER AND BUILD_TESTS)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/test TEST_SOURCES)

    add_executable (bwrap_test ${TEST_SOURCES})
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
    TARGET_LINK_LIBRARIES (container_test boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (container_test tiliae)

    ADD_TEST (container_test container_test)

ENDIF()

## DEMO ---------------------------------------------------

IF(BUILD_DEMO)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../demo/ DEMO_SOURCES)
         
    add_executable (demo ${DEMO_SOURCES})
    TARGET_LINK_LIBRARIES (demo boost_unit_test_framework)
    TARGET_LINK_LIBRARIES (demo tiliae)

ENDIF ()
