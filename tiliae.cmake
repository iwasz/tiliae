# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
# For clients, not for tiliae library itself.

FUNCTION (TILIAE_PARSE PARSER_PATH SUFFIX INPUT_FILE OUTPUT_FILE)
        ADD_CUSTOM_COMMAND (OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                COMMAND ${PARSER_PATH} -p compile_commands.json "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" -s "${SUFFIX}" -o "${CMAKE_CURRENT_SOURCE_DIR}/${OUTPUT_FILE}"
                DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}")
ENDFUNCTION ()


