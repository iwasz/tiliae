# +-------------------------------+
# | Generate reflection database. |
# +-------------------------------+
FUNCTION (TILIAE_PARSE PARSER_PATH INPUT_FILE OUTPUT_FILE)
        SET (DATABASE_DIR "${CMAKE_CURRENT_BINARY_DIR}/reflectionDatabase/${INPUT_FILE}")
        SET (DATABASE_FILE "${DATABASE_DIR}/ReflectionDatabase.cc")
        FILE (MAKE_DIRECTORY ${DATABASE_DIR})

        #MESSAGE (STATUS "Using reflection parser : ${PARSER_PATH}")

        ADD_CUSTOM_COMMAND (OUTPUT ${DATABASE_FILE}
                COMMAND ${PARSER_PATH} -p compile_commands.json "${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_FILE}" -o ${DATABASE_FILE}
                DEPENDS ${INPUT_FILE} tiliaeparser)

        SET (${OUTPUT_FILE} ${DATABASE_FILE} PARENT_SCOPE)
ENDFUNCTION ()
