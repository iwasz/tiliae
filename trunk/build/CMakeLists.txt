# Wymagaj tej wersji - dopiero w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.6.0 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Separate libraries like tiliaecore, tiliaecommon etc
SET(MULTI_LIB                0)
SET(SINGLE_LIB               1)

# Here we can set what to build actually (1=build, 0=do not build).
SET(BUILD_CORE               1)
SET(BUILD_CORE_TEST          1)
SET(BUILD_COMMON             1)
SET(BUILD_COMMON_TEST        1)
SET(BUILD_REFLECTION         1)
SET(BUILD_REFLECTION_TEST    1)
SET(BUILD_TEST_HELPERS       0)
SET(BUILD_FACTORY            0)
SET(BUILD_FACTORY_TEST       0)
SET(BUILD_EDITOR             0)
SET(BUILD_EDITOR_TEST        0)
SET(BUILD_BEAN_WRAPPER       0)
SET(BUILD_BEAN_WRAPPER_TEST  0)
SET(BUILD_K202               0)
SET(BUILD_K202_TEST          0)
SET(BUILD_SIGNAL             0)
SET(BUILD_SIGNAL_TEST        0)
SET(BUILD_STATE_MACHINE      0)
SET(BUILD_STATE_MACHINE_TEST 0)
SET(BUILD_XML                0)
SET(BUILD_XML_TEST           0)
SET(BUILD_CONTAINER          0)
SET(BUILD_CONTAINER_TEST     0)
SET(BUILD_DEMO               0)

#SET (CMAKE_VERBOSE_MAKEFILE 1) 
ADD_DEFINITIONS (-g -fvisibility=hidden -DTILIAE_DLL -Wall)
ADD_DEFINITIONS (-DTILIAE_DEBUG)
ADD_DEFINITIONS (-O0)

#ADD_DEFINITIONS (-fsyntax-only -fno-common)

# Dla icc
#ADD_DEFINITIONS (-w)

#SET (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#SET (LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
#SET (CMAKE_VERBOSE_MAKEFILE true)

#SET (CMAKE_C_COMPILER gcc-4.5)
#SET (CMAKE_CXX_COMPILER g++-4.5)
       
# Przyklad uzycia pkg-config, bo pewnie usune te wpisy z podkatalogow.
#include (FindPkgConfig)
#pkg_check_modules (TOOLS_DEPS "tiliaecore" "tiliaereflect")
#INCLUDE_DIRECTORIES (${TOOLS_DEPS_INCLUDE_DIRS})

# Prefix w którym będzie dokonywana instalacja (domyślnie /usr/local, a ja zmieniam na swój.)

#IF (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
#   SET (CMAKE_INSTALL_PREFIX "/home/iwasz/local2")
#ENDIF()

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/../src/"
    DESTINATION "include/tiliae" 
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

#INSTALL (
#    DIRECTORY "${PROJECT_SOURCE_DIR}/../src/"
#    DESTINATION "include/tiliae" 
#    FILES_MATCHING PATTERN "*.gch"
#    PATTERN "*.svn*" EXCLUDE
#    PATTERN "*test*" EXCLUDE)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/pc/"
    DESTINATION "/usr/lib/pkgconfig"
    FILES_MATCHING PATTERN "*.pc"
    PATTERN "*.svn*" EXCLUDE)

SET(Boost_ADDITIONAL_VERSIONS "1.41" "1.41.0")
find_package( Boost 1.41.0 )
include_directories(${Boost_INCLUDE_DIRS})

include (FindPkgConfig)
pkg_check_modules (XML "libxml-2.0")
INCLUDE_DIRECTORIES (${XML_INCLUDE_DIRS})
link_directories(${XML_LIBRARY_DIRS})

ENABLE_TESTING ()

SET(MULTI_LIB_SOURCES)


## --------------------------------------------------------
## Core
## --------------------------------------------------------
IF(BUILD_CORE)

    SET(LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/variant LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/string LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/core/)

    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)        
        
    IF(MULTI_LIB)
        add_library (tiliaecore SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaecore 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)
   
ENDIF(BUILD_CORE)
## --------------------------------------------------------
## TestHelpers
## --------------------------------------------------------
IF(BUILD_TEST_HELPERS)

    SET(LIB_SOURCES)    
    AUX_SOURCE_DIRECTORY (../src/testHelpers LIB_SOURCES)
    INCLUDE_DIRECTORIES (../src/testHelpers)
    #add_library (tiliaetesthelpers SHARED ${THELP_SOURCES})

ENDIF(BUILD_TEST_HELPERS)
## --------------------------------------------------------
## Common
## --------------------------------------------------------
IF(BUILD_COMMON)

    SET(LIB_SOURCES)    
    AUX_SOURCE_DIRECTORY (../src/common/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/logger LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/path LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/collection LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/common/)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)        
    
    IF(MULTI_LIB)
        add_library (tiliaecommon SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaecommon 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_COMMON)
## --------------------------------------------------------
## Reflection
## --------------------------------------------------------
IF(BUILD_REFLECTION)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/reflection/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/wrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/annotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/visitor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/reflectAnnotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/model LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/reflection)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
        
    IF(MULTI_LIB)
        add_library (tiliaereflection SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaereflection 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

#    GET_DIRECTORY_PROPERTY(DIRINC INCLUDE_DIRECTORIES)
    
#    FOREACH(item ${DIRINC})
#        LIST(APPEND MY_INC  -I${item})
#    ENDFOREACH(item)
#
#    #file (GLOB_RECURSE MY_FILE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ../src/core/*.h)    
#    file (GLOB_RECURSE MY_FILE ../src/reflection/Reflection.h)    
#    
#    
#    FOREACH (item ${MY_FILE})
#        GET_FILENAME_COMPONENT (MY_PATH "${item}" PATH)
#        ADD_CUSTOM_COMMAND (TARGET tiliaecore POST_BUILD COMMAND ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_FLAGS} ${MY_INC} -I${MY_PATH} -x c++-header ${item})
#    ENDFOREACH(item)

ENDIF(BUILD_REFLECTION)
## --------------------------------------------------------
## BeanWrapper
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/plugins LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/misc LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/beanWrapper) 
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
        
    IF(MULTI_LIB)
        add_library (tiliaebeanwrapper SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaebeanwrapper 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_BEAN_WRAPPER)
## --------------------------------------------------------
## Factory
## --------------------------------------------------------
IF(BUILD_FACTORY)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/factory LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/factory)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
        
    IF(MULTI_LIB)
        add_library (tiliaefactory SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaefactory 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_FACTORY)
## --------------------------------------------------------
## Editor
## --------------------------------------------------------
IF(BUILD_EDITOR)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/editor LIB_SOURCES)
    #AUX_SOURCE_DIRECTORY (../src/editor/mappedEditor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/scalar LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/editor)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
        
    IF(MULTI_LIB)
        add_library (tiliaeeditor SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaeeditor 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_EDITOR)
## --------------------------------------------------------
## K202 expression script
## --------------------------------------------------------
IF(BUILD_K202)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/k202 LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/compiler LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/expression LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/misc LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/extension LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/k202/)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      

    IF(MULTI_LIB)
        add_library (tiliaek202 SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaek202 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_K202)
## --------------------------------------------------------
## Signal                  
## --------------------------------------------------------
IF(BUILD_SIGNAL)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/signal LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/signal/)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      

    IF(MULTI_LIB)
        add_library (tiliaesignal SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaesignal 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_SIGNAL)
## --------------------------------------------------------
## StateMachine
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/stateMachine/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/condition LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/extension LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/input LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/output LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/action LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/context LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/transition LIB_SOURCES)
    
    INCLUDE_DIRECTORIES (../src/stateMachine)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      

    IF(MULTI_LIB)
        add_library (tiliaestatemachine SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaestatemachine 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_STATE_MACHINE)
## --------------------------------------------------------
## xml
## --------------------------------------------------------
IF(BUILD_XML)

    SET(LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/xml LIB_SOURCES)
    INCLUDE_DIRECTORIES (../src/xml)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
    
    IF(MULTI_LIB)
        add_library (tiliaexml SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaexml 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_XML)
## --------------------------------------------------------
## container
## --------------------------------------------------------
IF(BUILD_CONTAINER)

    SET(LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (../src/container LIB_SOURCES)
    
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/factory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/service LIB_SOURCES)
    #AUX_SOURCE_DIRECTORY (../src/container/beanFactory/visitor LIB_SOURCES)
       
    AUX_SOURCE_DIRECTORY (../src/container/common LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/id LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (../src/container/inputFormat LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/xml/ LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (../src/container/metaStructure LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/service LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/data LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/elem LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/model/meta LIB_SOURCES)
  
    INCLUDE_DIRECTORIES (../src/container)
    
    IF(SINGLE_LIB)
        LIST (APPEND MULTI_LIB_SOURCES ${LIB_SOURCES})
    ENDIF(SINGLE_LIB)      
    
    IF(MULTI_LIB)
        add_library (tiliaecontainer SHARED ${LIB_SOURCES})

        INSTALL (
            TARGETS tiliaecontainer 
            DESTINATION lib 
            PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE)
    ENDIF(MULTI_LIB)

ENDIF(BUILD_CONTAINER)
## --------------------------------------------------------
## Biblioteka Tiliae - all in one.
## --------------------------------------------------------

IF(SINGLE_LIB)
    add_library (tiliae SHARED ${MULTI_LIB_SOURCES})

    INSTALL (
        TARGETS tiliae
        DESTINATION lib 
        PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE)
ENDIF(SINGLE_LIB)

## --------------------------------------------------------
## Testy.
## --------------------------------------------------------
IF(BUILD_CORE_TEST)

    SET(SOURCES)
    AUX_SOURCE_DIRECTORY (../src/core/test SOURCES)
    add_executable (core_test ${SOURCES})
    
    TARGET_LINK_LIBRARIES (core_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (core_test boost_prg_exec_monitor-gcc44)
    
    #To jest programik do optymalizacji pod kątem wielkości binarek
    IF (0)
        SET(SOURCES)
        AUX_SOURCE_DIRECTORY (../src/core/test/testSize SOURCES)
        add_executable (sizeLight ${SOURCES})
        TARGET_LINK_LIBRARIES (sizeLight tiliaecore)
    ENDIF()
    
    IF(MULTI_LIB)
        TARGET_LINK_LIBRARIES (core_test tiliaecore)
    ELSE(MULTI_LIB)
        TARGET_LINK_LIBRARIES (core_test tiliae)
        TARGET_LINK_LIBRARIES (core_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (core_test core_test)

ENDIF(BUILD_CORE_TEST)
## --------------------------------------------------------
IF(BUILD_COMMON_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/common/test TEST_SOURCES)
    
    add_executable (common_test ${TEST_SOURCES})
    
    TARGET_LINK_LIBRARIES (common_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (common_test boost_prg_exec_monitor-gcc44)
    
    IF(MULTI_LIB)
        TARGET_LINK_LIBRARIES (common_test tiliaecore)
        TARGET_LINK_LIBRARIES (common_test tiliaecommon)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (common_test tiliae)
        TARGET_LINK_LIBRARIES (common_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (common_test common_test)

ENDIF(BUILD_COMMON_TEST)
## --------------------------------------------------------
IF(BUILD_REFLECTION_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/reflection/test/testHelpers TEST_SOURCES)
    
    add_executable (reflection_test ${TEST_SOURCES})
    
    TARGET_LINK_LIBRARIES (reflection_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (reflection_test boost_prg_exec_monitor-gcc44)
    
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (reflection_test tiliaecore)
        TARGET_LINK_LIBRARIES (reflection_test tiliaereflection)
        TARGET_LINK_LIBRARIES (reflection_test tiliaecommon)        
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (reflection_test tiliae)
        TARGET_LINK_LIBRARIES (reflection_test ${XML_LIBRARIES})        
    ENDIF(MULTI_LIB)

    ADD_TEST (reflection_test reflection_test)

ENDIF(BUILD_REFLECTION_TEST)
## --------------------------------------------------------
IF(BUILD_TOOLS_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/tools/test TEST_SOURCES)
    add_executable (tools_test ${TEST_SOURCES})  
    TARGET_LINK_LIBRARIES (tools_test boost_prg_exec_monitor-gcc44)
    
    IF(MULTI_LIB)
        TARGET_LINK_LIBRARIES (tools_test tiliaecore)
        TARGET_LINK_LIBRARIES (tools_test tiliaereflection)
        TARGET_LINK_LIBRARIES (tools_test tiliaetools)
        TARGET_LINK_LIBRARIES (tools_test tiliaecommon)
        
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (tools_test tiliae)
        TARGET_LINK_LIBRARIES (tools_test ${XML_LIBRARIES})        
    ENDIF(MULTI_LIB)

    ADD_TEST (tools_test tools_test)

ENDIF(BUILD_TOOLS_TEST)
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/beanWrapper/test TEST_SOURCES)
    add_executable (bwrap_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (bwrap_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (bwrap_test boost_prg_exec_monitor-gcc44)
    
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (bwrap_test tiliaecore)
        TARGET_LINK_LIBRARIES (bwrap_test tiliaereflection)
        TARGET_LINK_LIBRARIES (bwrap_test tiliaetools)
        TARGET_LINK_LIBRARIES (bwrap_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (bwrap_test tiliaecommon)

    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (bwrap_test tiliae)
        TARGET_LINK_LIBRARIES (bwrap_test ${XML_LIBRARIES})        
    ENDIF(MULTI_LIB)

    ADD_TEST (bwrap_test bwrap_test)

ENDIF(BUILD_BEAN_WRAPPER_TEST)
## --------------------------------------------------------
IF(BUILD_FACTORY_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/factory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/factory/testHelpers TEST_SOURCES)
    
    add_executable (factory_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (factory_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (factory_test boost_prg_exec_monitor-gcc44)
    
    IF(MULTI_LIB)       
        TARGET_LINK_LIBRARIES (factory_test tiliaecore)
        TARGET_LINK_LIBRARIES (factory_test tiliaereflection)
        TARGET_LINK_LIBRARIES (factory_test tiliaetools)
        TARGET_LINK_LIBRARIES (factory_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (factory_test tiliaecommon)
        TARGET_LINK_LIBRARIES (factory_test tiliaefactory)
        TARGET_LINK_LIBRARIES (factory_test tiliaeeditor)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (factory_test tiliae)
        TARGET_LINK_LIBRARIES (factory_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (factory_test factory_test)

ENDIF(BUILD_FACTORY_TEST)
## --------------------------------------------------------
IF(BUILD_EDITOR_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/testHelpers TEST_SOURCES)
    add_executable (editor_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (editor_test boost_prg_exec_monitor-gcc44)
    TARGET_LINK_LIBRARIES (editor_test boost_unit_test_framework-gcc44)
    
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (editor_test tiliaecore)
        TARGET_LINK_LIBRARIES (editor_test tiliaereflection)
        TARGET_LINK_LIBRARIES (editor_test tiliaetools)
        TARGET_LINK_LIBRARIES (editor_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (editor_test tiliaecommon)
        TARGET_LINK_LIBRARIES (editor_test tiliaefactory)
        TARGET_LINK_LIBRARIES (editor_test tiliaeeditor)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (editor_test tiliae)
        TARGET_LINK_LIBRARIES (editor_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (editor_test editor_test)

ENDIF(BUILD_EDITOR_TEST)
## --------------------------------------------------------
IF(BUILD_K202_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/k202/test TEST_SOURCES)
    add_executable (k202_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (k202_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (k202_test boost_prg_exec_monitor-gcc44)
        
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (k202_test tiliaecore)
        TARGET_LINK_LIBRARIES (k202_test tiliaereflection)
        TARGET_LINK_LIBRARIES (k202_test tiliaetools)
        TARGET_LINK_LIBRARIES (k202_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (k202_test tiliaecommon)
        TARGET_LINK_LIBRARIES (k202_test tiliaek202)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (k202_test tiliae)
        TARGET_LINK_LIBRARIES (k202_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (k202_test k202_test)

ENDIF(BUILD_K202_TEST)
## --------------------------------------------------------
IF(BUILD_SIGNAL_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/signal/test TEST_SOURCES)
    add_executable (signal_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (signal_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (signal_test boost_prg_exec_monitor-gcc44)
        
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (signal_test tiliaecore)
        TARGET_LINK_LIBRARIES (signal_test tiliaereflection)
        TARGET_LINK_LIBRARIES (signal_test tiliaetools)
        TARGET_LINK_LIBRARIES (signal_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (signal_test tiliaecommon)
        TARGET_LINK_LIBRARIES (signal_test tiliaek202)
        TARGET_LINK_LIBRARIES (signal_test tiliaesignal)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (signal_test tiliae)
        TARGET_LINK_LIBRARIES (signal_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (signal_test signal_test)

ENDIF(BUILD_SIGNAL_TEST)
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/stateMachine/test TEST_SOURCES)
    add_executable (machine_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (machine_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (machine_test boost_prg_exec_monitor-gcc44)    
    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (machine_test tiliaecore)
        TARGET_LINK_LIBRARIES (machine_test tiliaereflection)
        TARGET_LINK_LIBRARIES (machine_test tiliaetools)
        TARGET_LINK_LIBRARIES (machine_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (machine_test tiliaecommon)
        TARGET_LINK_LIBRARIES (machine_test tiliaestatemachine)
        TARGET_LINK_LIBRARIES (machine_test tiliaek202)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (machine_test tiliae)
        TARGET_LINK_LIBRARIES (machine_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (machine_test machine_test)

ENDIF(BUILD_STATE_MACHINE_TEST)
## --------------------------------------------------------
IF(BUILD_XML_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/xml/test TEST_SOURCES)   
    add_executable (xml_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (xml_test boost_unit_test_framework-gcc44)
    TARGET_LINK_LIBRARIES (xml_test boost_prg_exec_monitor-gcc44)
        
    IF(MULTI_LIB)       
        TARGET_LINK_LIBRARIES (xml_test ${XML_LIBRARIES})
        TARGET_LINK_LIBRARIES (xml_test tiliaecore)
        TARGET_LINK_LIBRARIES (xml_test tiliaereflection)
        TARGET_LINK_LIBRARIES (xml_test tiliaetools)
        TARGET_LINK_LIBRARIES (xml_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (xml_test tiliaecommon)
        TARGET_LINK_LIBRARIES (xml_test tiliaexml)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (xml_test tiliae)
        TARGET_LINK_LIBRARIES (xml_test ${XML_LIBRARIES})        
    ENDIF(MULTI_LIB)

    ADD_TEST (xml_test xml_test)

ENDIF(BUILD_XML_TEST)
## container test -----------------------------------------
IF(BUILD_CONTAINER_TEST)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/beanFactory/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/common/testHelpers TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/inputFormat/xml/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/container/metaStructure/test TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../src/editor/testHelpers TEST_SOURCES)
     
    add_executable (container_test ${TEST_SOURCES})
    TARGET_LINK_LIBRARIES (container_test boost_unit_test_framework-gcc44)

    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (container_test ${XML_LIBRARIES})
        TARGET_LINK_LIBRARIES (container_test tiliaecore)
        TARGET_LINK_LIBRARIES (container_test tiliaereflection)
        TARGET_LINK_LIBRARIES (container_test tiliaetools)
        TARGET_LINK_LIBRARIES (container_test tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (container_test tiliaecommon)
        TARGET_LINK_LIBRARIES (container_test tiliaexml)
        TARGET_LINK_LIBRARIES (container_test tiliaecontainer)
        TARGET_LINK_LIBRARIES (container_test tiliaefactory)
        TARGET_LINK_LIBRARIES (container_test tiliaeeditor)
        TARGET_LINK_LIBRARIES (container_test tiliaek202)
        TARGET_LINK_LIBRARIES (container_test tiliaestatemachine)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (container_test tiliae)
        TARGET_LINK_LIBRARIES (container_test ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

    ADD_TEST (container_test container_test)

ENDIF(BUILD_CONTAINER_TEST)


# To generalnie nie działa nie dla tego, że są złe targety, czy coś, tylk przez to, że CMake robi sobie
# specjalne podkatalogi dla swoich głownych targetów, a dla tych podanych przeze mnie nie. Dlatego nie 
# działa. Tak myślę.
##add_custom_target (testIwasz DEPENDS all test)

#add_custom_target (test ALL)
#add_custom_target (check ALL)
#add_dependencies (check test)
#add_dependencies (check test)

# Wystarczy w Makefile do targetu test dodać dependency all i potem zrobić make test i jest OK. A jak to uzyskać z poziomy CMakeLists? DUPA.
#test: all


## DEMO ---------------------------------------------------
IF(BUILD_DEMO)

    SET(TEST_SOURCES)
    AUX_SOURCE_DIRECTORY (../demo/ DEMO_SOURCES)
         
    add_executable (demo ${DEMO_SOURCES})
    TARGET_LINK_LIBRARIES (demo boost_unit_test_framework-gcc44)

    IF(MULTI_LIB)        
        TARGET_LINK_LIBRARIES (demo ${XML_LIBRARIES})
        TARGET_LINK_LIBRARIES (demo tiliaecore)
        TARGET_LINK_LIBRARIES (demo tiliaereflection)
        TARGET_LINK_LIBRARIES (demo tiliaetools)
        TARGET_LINK_LIBRARIES (demo tiliaebeanwrapper)
        TARGET_LINK_LIBRARIES (demo tiliaecommon)
        TARGET_LINK_LIBRARIES (demo tiliaexml)
        TARGET_LINK_LIBRARIES (demo tiliaecontainer)
        TARGET_LINK_LIBRARIES (demo tiliaefactory)
        TARGET_LINK_LIBRARIES (demo tiliaeeditor)
        TARGET_LINK_LIBRARIES (demo tiliaek202)
        TARGET_LINK_LIBRARIES (demo tiliaestatemachine)
    ELSE (MULTI_LIB)
        TARGET_LINK_LIBRARIES (demo tiliae)
        TARGET_LINK_LIBRARIES (demo ${XML_LIBRARIES})
    ENDIF(MULTI_LIB)

ENDIF ()
