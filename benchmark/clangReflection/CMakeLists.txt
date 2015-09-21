# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)
project (clangReflection)

#TODO !!! -Wall
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE INTERNAL "cxx compiler flags")

SET(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Wall" CACHE INTERNAL "c release compiler flags")
SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -std=c++11" CACHE INTERNAL "cxx release compiler flags")

#SET(CMAKE_CXX_LINK_EXECUTABLE "ld" CACHE INTERNAL "")

ADD_DEFINITIONS (-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS (-DREFLECTION_ENABLED)

SET (CMAKE_VERBOSE_MAKEFILE off)

include (FindPkgConfig)

pkg_check_modules (TILIAE "tiliae")
if (NOT TILIAE_FOUND)
        message ("Tiliae not installed, using local copy.")
        SET (TILIAE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../../src/")
        SET (TILIAE_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../../build/")
        SET (TILIAE_LIBRARIES "tiliae")
        message (${TILIAE_INCLUDE_DIRS})
        message (${TILIAE_LIBRARY_DIRS})
endif ()
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
link_directories(${TILIAE_LIBRARY_DIRS})

# Sources
AUX_SOURCE_DIRECTORY (./ SOURCES)

add_executable (${CMAKE_PROJECT_NAME} ${SOURCES})
#add_executable (${CMAKE_PROJECT_NAME} main.cc Reflection.cc)

TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TILIAE_LIBRARIES})
