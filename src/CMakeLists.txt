CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Here we can set what to build actually (1=build, 0=do not build).
SET (BUILD_CORE                ON CACHE BOOL "")
SET (BUILD_COMMON              ON CACHE BOOL "")
SET (BUILD_REFLECTION          ON CACHE BOOL "")
SET (BUILD_TEST_HELPERS        ON CACHE BOOL "Buduje tylko gdy BUILD_TESTS true")
SET (BUILD_FACTORY             ON CACHE BOOL "")
SET (BUILD_EDITOR              ON CACHE BOOL "")
SET (BUILD_BEAN_WRAPPER        ON CACHE BOOL "")
SET (BUILD_K202                ON CACHE BOOL "")
SET (BUILD_SIGNAL              ON CACHE BOOL "")
SET (BUILD_STATE_MACHINE       OFF CACHE BOOL "")
SET (BUILD_CONTAINER           ON CACHE BOOL "")
SET (BUILD_DEMO                OFF CACHE BOOL "Whether to build demo, or not.")
SET (BUILD_TESTS               OFF CACHE BOOL "Whether to build tests, or not.")
SET (WITH_CORE_STRING          OFF CACHE BOOL "Deprecated.")
SET (WITH_PARSER               ON CACHE BOOL "Reflection with custom clang parser.")
SET (WITH_ANNOTATIONS          OFF CACHE BOOL "Reflection with annotations.")

if (WITH_CORE_STRING)
    add_definitions (-DWITH_CORE_STRING)
endif ()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    SET (BUILD_DEMO                0)
    SET (BUILD_TESTS               0)
endif()

if (WITH_CORE_STRING)
    add_definitions (-DWITH_CORE_STRING)
endif ()

#SET (TARGET_PLATFORM "" CACHE STRING "Na jaka platforme budujemy")
#SET_PROPERTY (CACHE TARGET_PLATFORM PROPERTY STRINGS Linux Windows Android iPhone)

SET (CMAKE_C_FLAGS " -DTILIAE_DLL -DALLOW_CAST_TO_SMART ")
SET (CMAKE_CXX_FLAGS "-DTILIAE_DLL -DALLOW_CAST_TO_SMART -std=c++11 -stdlib=libc++")
#ADD_DEFINITIONS (-Wall)

#SET (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined")
#SET (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-undefined")
SET (CMAKE_VERBOSE_MAKEFILE OFF)

INSTALL (
    DIRECTORY "${PROJECT_SOURCE_DIR}/src/"
    DESTINATION "include/tiliae"
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*.git*" EXCLUDE
    PATTERN "*test*" EXCLUDE)

INSTALL (
    DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/pc/"
    DESTINATION "lib/pkgconfig"
    FILES_MATCHING PATTERN "*.pc"
    PATTERN "*.svn*" EXCLUDE
    PATTERN "*.git*" EXCLUDE)

find_package (Boost REQUIRED COMPONENTS system prg_exec_monitor unit_test_framework)
include_directories(${Boost_INCLUDE_DIRS})
link_directories (${Boost_LIBRARY_DIRS})

include (FindPkgConfig)
pkg_check_modules (MXML REQUIRED "mxml")
INCLUDE_DIRECTORIES (${MXML_INCLUDE_DIRS})
link_directories(${MXML_LIBRARY_DIRS})

IF (WITH_ANNOTATIONS)
        MESSAGE (STATUS "Building reflection with annotations.")
        ADD_DEFINITIONS (-DWITH_ANNOTATIONS)
ENDIF ()

IF (WITH_PARSER)
        MESSAGE (STATUS "Building reflection with parser.")
        ADD_DEFINITIONS (-DWITH_PARSER)
ENDIF ()

INCLUDE_DIRECTORIES (./)

## --------------------------------------------------------
## Core
## --------------------------------------------------------
IF(BUILD_CORE)
    ADD_DEFINITIONS (-DBUILD_CORE)
    AUX_SOURCE_DIRECTORY (core LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (core/variant LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (core/string LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (core/allocator LIB_SOURCES)
ENDIF(BUILD_CORE)
## --------------------------------------------------------
## Common
## --------------------------------------------------------
IF(BUILD_COMMON)
    ADD_DEFINITIONS (-DBUILD_COMMON)
    AUX_SOURCE_DIRECTORY (common/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (common/logger LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (common/path LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (common/collection LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (common/dataSource LIB_SOURCES)
ENDIF(BUILD_COMMON)
## --------------------------------------------------------
## Reflection
## --------------------------------------------------------
IF(BUILD_REFLECTION)
    ADD_DEFINITIONS (-DBUILD_REFLECTION)
    AUX_SOURCE_DIRECTORY (reflection/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/wrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/annotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/visitor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/reflectAnnotations LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (reflection/model LIB_SOURCES)
ENDIF(BUILD_REFLECTION)
## --------------------------------------------------------
## BeanWrapper
## --------------------------------------------------------
IF(BUILD_BEAN_WRAPPER)
    ADD_DEFINITIONS (-DBUILD_BEAN_WRAPPER)
    AUX_SOURCE_DIRECTORY (beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (beanWrapper/beanWrapper LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (beanWrapper/plugins LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (beanWrapper/misc LIB_SOURCES)
ENDIF(BUILD_BEAN_WRAPPER)
## --------------------------------------------------------
## Factory
## --------------------------------------------------------
IF(BUILD_FACTORY)
    ADD_DEFINITIONS (-DBUILD_FACTORY)
    AUX_SOURCE_DIRECTORY (factory LIB_SOURCES)
ENDIF(BUILD_FACTORY)
## --------------------------------------------------------
## Editor
## --------------------------------------------------------
IF(BUILD_EDITOR)
    ADD_DEFINITIONS (-DBUILD_EDITOR)
    AUX_SOURCE_DIRECTORY (editor LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (editor/scalar LIB_SOURCES)
ENDIF(BUILD_EDITOR)
## --------------------------------------------------------
## K202 expression script
## --------------------------------------------------------
IF(BUILD_K202)
    ADD_DEFINITIONS (-DBUILD_K202)
    AUX_SOURCE_DIRECTORY (k202 LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (k202/compiler LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (k202/expression LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (k202/misc LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (k202/extension LIB_SOURCES)
ENDIF(BUILD_K202)
## --------------------------------------------------------
## Signal
## --------------------------------------------------------
IF(BUILD_SIGNAL)
    ADD_DEFINITIONS (-DBUILD_SIGNAL)
    AUX_SOURCE_DIRECTORY (signal LIB_SOURCES)
ENDIF(BUILD_SIGNAL)
## --------------------------------------------------------
## StateMachine
## --------------------------------------------------------
IF(BUILD_STATE_MACHINE)
    ADD_DEFINITIONS (-DBUILD_STATE_MACHINE)
    AUX_SOURCE_DIRECTORY (stateMachine/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/condition LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/extension LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/input LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/output LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/action LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/context LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (stateMachine/transition LIB_SOURCES)
ENDIF(BUILD_STATE_MACHINE)
## --------------------------------------------------------
## container
## --------------------------------------------------------
IF(BUILD_CONTAINER)
    ADD_DEFINITIONS (-DBUILD_CONTAINER)
    AUX_SOURCE_DIRECTORY (container LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (container/beanFactory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/beanFactory/factory LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/beanFactory/service LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (container/common LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/common/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/common/id LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (container/inputFormat LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/inputFormat/mxml/ LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/inputFormat/compact/ LIB_SOURCES)

    AUX_SOURCE_DIRECTORY (container/metaStructure LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/interface LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/service LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/model LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/model/data LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/model/elem LIB_SOURCES)
    AUX_SOURCE_DIRECTORY (container/metaStructure/model/meta LIB_SOURCES)
ENDIF(BUILD_CONTAINER)

## --------------------------------------------------------
## Biblioteka Tiliae - all in one.
## --------------------------------------------------------

IF (WITH_PARSER)
        TILIAE_PARSE ("${CMAKE_BINARY_DIR}/parser/tiliaeparser" "tiliae" "Reflection_input.cc" "Reflection_output_tiliae.cc.h")
        LIST (APPEND LIB_SOURCES "Reflection_input.cc")
        LIST (APPEND LIB_SOURCES "Reflection_output_tiliae.cc.h")
ENDIF ()

SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (ANDROID)
    add_library (tiliae STATIC ${LIB_SOURCES})
else ()
    add_library (tiliae SHARED ${LIB_SOURCES})
    TARGET_LINK_LIBRARIES (tiliae ${MXML_LIBRARIES})
    TARGET_LINK_LIBRARIES (tiliae c++abi)
    add_dependencies (tiliae tiliaeparser)
endif ()


#IF (WITH_PARSER)
#        TILIAE_PARSE (tiliae "${CMAKE_BINARY_DIR}/parser/tiliaeparser")
#ENDIF()

INSTALL (
    TARGETS tiliae
    DESTINATION lib
    PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE
    GROUP_READ GROUP_EXECUTE
    WORLD_READ WORLD_EXECUTE)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/../pc/tiliae.pc.in ${CMAKE_CURRENT_BINARY_DIR}/pc/tiliae.pc @ONLY)
