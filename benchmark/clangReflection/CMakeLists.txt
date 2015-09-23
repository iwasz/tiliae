# Wymagaj tej wersji - dopier w niej jest nowe makro FindPkgConfig
CMAKE_MINIMUM_REQUIRED (VERSION 2.4.7 FATAL_ERROR)
PROJECT (clangReflection)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" CACHE INTERNAL "cxx compiler flags")
SET (CMAKE_C_FLAGS_RELEASE "-DNDEBUG -Wall" CACHE INTERNAL "c release compiler flags")
SET (CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -std=c++11" CACHE INTERNAL "cxx release compiler flags")

#SET(CMAKE_CXX_LINK_EXECUTABLE "ld" CACHE INTERNAL "")

ADD_DEFINITIONS (-DBOOST_LOG_DYN_LINK)
ADD_DEFINITIONS (-DREFLECTION_ENABLED)

SET (CMAKE_VERBOSE_MAKEFILE off)

INCLUDE (FindPkgConfig)

PKG_CHECK_MODULES (TILIAE "tiliae")
IF (NOT TILIAE_FOUND)
        MESSAGE (STATUS "Tiliae not installed, using local copy.")
        SET (TILIAE_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/../../src/")
        SET (TILIAE_LIBRARY_DIRS "${PROJECT_SOURCE_DIR}/../../build/")
        SET (TILIAE_LIBRARIES "tiliae")
        MESSAGE (STATUS ${TILIAE_INCLUDE_DIRS})
        MESSAGE (STATUS ${TILIAE_LIBRARY_DIRS})
ENDIF ()
INCLUDE_DIRECTORIES (${TILIAE_INCLUDE_DIRS})
LINK_DIRECTORIES (${TILIAE_LIBRARY_DIRS})

# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
FILE (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/reflectionDatabase)
FIND_PROGRAM (REFLECTION_PARSER NAME "tiliaeparser" HINTS "${PROJECT_SOURCE_DIR}/../../parser/build/")

IF (NOT REFLECTION_PARSER)
        MESSAGE(FATAL_ERROR "reflectionParser not found -- ${REFLECTION_PARSER}")
ENDIF()

MESSAGE (STATUS "Found REFLECTION_PARSER as ${REFLECTION_PARSER}")

ADD_CUSTOM_COMMAND (OUTPUT ${CMAKE_BINARY_DIR}/reflectionDatabase/ReflectionDatabase.cc
        COMMAND ${REFLECTION_PARSER} -p compile_commands.json ${CMAKE_SOURCE_DIR}/Refl.cc -o ${CMAKE_BINARY_DIR}/reflectionDatabase/ReflectionDatabase.cc
        DEPENDS ${CMAKE_SOURCE_DIR}/Refl.cc
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

LIST (APPEND SOURCES ${CMAKE_BINARY_DIR}/reflectionDatabase/ReflectionDatabase.cc)
# http://stackoverflow.com/questions/19642590/libtooling-cant-find-stddef-h-nor-other-headers
# http://clang.llvm.org/docs/FAQ.html#i-get-errors-about-some-headers-being-missing-stddef-h-stdarg-h
# http://clang.llvm.org/docs/LibTooling.html#libtooling-builtin-includes
#
# Programs wiritten with libtooling expect that they are fired from within clang root directory.
# Every such program would look for system headers (like stdarg.h) in a path relative to clang
# root. So here's workaround since we are outside the clang root:
# (fixes libtooling app, breaks the build) ADD_DEFINITIONS (-isystem /home/liwaszkiewicz/local/share/llvm/lib/clang/3.8.0/include)

# Powyższe powoduje, że parser działa, ale kod się nie kopiluje :( może z powodu clang-3.6.0 -> 3.8.0?

# +-------------------------------+
# | Main target                   |
# +-------------------------------+
# It must be here, right before add_executable, otherwise json would not get created due to
# ADD_CUSTOM_COMMAND which it don't know how to handle. If ADD_CUSTOM_COMMAND is removed,
# json gets created regardless the position of SET (CMAKE_EXPORT_COMPILE_COMMANDS ON) in the
# CMakeLists.txt (can be on the top in this situation).
SET (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sources
AUX_SOURCE_DIRECTORY (./ SOURCES)
ADD_EXECUTABLE (${CMAKE_PROJECT_NAME} ${SOURCES})
TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME} ${TILIAE_LIBRARIES})
