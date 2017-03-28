CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0048 NEW)
endif(COMMAND cmake_policy)

project (tiliae VERSION 0.9)

SET (WITH_PARSER ON CACHE BOOL "Reflection with custom clang parser.")
SET (WITH_CPPABI ON CACHE BOOL "Reflection with custom clang parser.")

IF (WITH_PARSER)
FUNCTION (TILIAE_PARSE PARSER_PATH SUFFIX INPUT_FILE OUTPUT_FILE)
        ADD_CUSTOM_COMMAND (OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                COMMAND ${PARSER_PATH} -p compile_commands.json "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" -s "${SUFFIX}" -o "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" tiliaeparser)
ENDFUNCTION ()

add_subdirectory (parser)
ENDIF ()
add_subdirectory (src)
add_subdirectory (test)
