CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

project (tiliae)
include (tiliae.cmake)

add_subdirectory (parser)
add_subdirectory (src)
add_subdirectory (test)
