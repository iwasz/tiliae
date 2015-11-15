CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)

project (tiliae)

FUNCTION (TILIAE_PARSE PARSER_PATH SUFFIX INPUT_FILE OUTPUT_FILE)
        ADD_CUSTOM_COMMAND (OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                COMMAND ${PARSER_PATH} -p compile_commands.json "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" -s "${SUFFIX}" -o "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" tiliaeparser)

#        SET (INPUT_FILE "Reflection_input.cc")
#        SET (OUTPUT_FILE "Reflection_output_${TARGET}.cc.h")
#        ADD_CUSTOM_COMMAND (TARGET ${TARGET} PRE_BUILD
#                COMMAND ${PARSER_PATH} -p compile_commands.json "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" -s "${SUFFIX}" -o "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
#                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" tiliaeparser)
ENDFUNCTION ()

add_subdirectory (parser)
add_subdirectory (src)
add_subdirectory (test)
