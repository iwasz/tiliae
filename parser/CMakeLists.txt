CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
#SET (CMAKE_VERBOSE_MAKEFILE ON)

FIND_PROGRAM (LLVM_CONFIG_PATH NAME "llvm-config-3.9" HINTS "${LLVM_ROOT}/bin")

IF (NOT LLVM_CONFIG_PATH)
        MESSAGE(FATAL_ERROR "llvm-config not found -- ${LLVM_CONFIG_PATH}")
ENDIF()

MESSAGE (STATUS "Found LLVM_CONFIG_PATH as ${LLVM_CONFIG_PATH}")


# This function saves the output of the llvm-config command with the given
# switch to the variable named VARNAME.
#
# Example usage: llvm_config(LLVM_CXXFLAGS "--cxxflags")
function (llvm_config VARNAME switch)
        set(CONFIG_COMMAND "${LLVM_CONFIG_PATH}" "${switch}")

        execute_process(
                COMMAND ${CONFIG_COMMAND}
                RESULT_VARIABLE HAD_ERROR
                OUTPUT_VARIABLE CONFIG_OUTPUT
        )

        if (HAD_ERROR)
                string(REPLACE ";" " " CONFIG_COMMAND_STR "${CONFIG_COMMAND}")
                message(STATUS "${CONFIG_COMMAND_STR}")
                message(FATAL_ERROR "llvm-config failed with status ${HAD_ERROR}")
        endif()

        # replace linebreaks with semicolon
        string (REGEX REPLACE "[ \t]*[\r\n]+[ \t]*" ";" CONFIG_OUTPUT ${CONFIG_OUTPUT})

        # make result available outside
        set(${VARNAME} ${CONFIG_OUTPUT} PARENT_SCOPE)

        # Optionally output the configured value
        message(STATUS "llvm_config(${VARNAME})=>${CONFIG_OUTPUT}")

        # cleanup
        unset(CONFIG_COMMAND)
endfunction(llvm_config)


llvm_config(LLVM_CXXFLAGS "--cxxflags")
llvm_config(LLVM_LDFLAGS "--ldflags")
llvm_config(LLVM_LIBS "--libs")
llvm_config(LLVM_LIBDIR "--libdir")
llvm_config(LLVM_INCLUDE_DIR "--includedir")
llvm_config(LLVM_SYSTEM_LIBS "--system-libs")

ADD_EXECUTABLE (tiliaeparser main.cc)
SET_TARGET_PROPERTIES (tiliaeparser PROPERTIES COMPILE_FLAGS "${LLVM_CXXFLAGS} -std=c++11")
SET_TARGET_PROPERTIES (tiliaeparser PROPERTIES INCLUDE_DIRECTORIES "${LLVM_INCLUDE_DIR}")
SET_TARGET_PROPERTIES (tiliaeparser PROPERTIES LINK_DIRECTORIES "${LLVM_LIBDIR}")

TARGET_LINK_LIBRARIES(tiliaeparser
  clangFrontend
  clangSerialization
  clangDriver
  clangParse
  clangSema
  clangAnalysis
  clangAST
  clangASTMatchers
  clangBasic
  clangEdit
  clangLex
  clangTooling
  LLVM
)

INCLUDE (FindCurses)

TARGET_LINK_LIBRARIES (tiliaeparser
    pthread
    z
    dl
    ${CURSES_LIBRARIES}
)

# lib and include are mandatory.
add_custom_command(
    TARGET tiliaeparser POST_BUILD
    COMMAND ln -sf ${LLVM_LIBDIR} ${CMAKE_BINARY_DIR}/lib
    COMMAND ln -sf ${LLVM_INCLUDE_DIR} ${CMAKE_BINARY_DIR}/include
)
