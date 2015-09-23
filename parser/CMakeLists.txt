CMAKE_MINIMUM_REQUIRED (VERSION 2.8 FATAL_ERROR)
PROJECT (tiliaeparser)
SET (CMAKE_VERBOSE_MAKEFILE 0)

FIND_PROGRAM (LLVM_CONFIG_PATH NAME "llvm-config" HINTS "${LLVM_ROOT}/bin")

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


add_definitions(${LLVM_CXXFLAGS})
add_definitions (-std=c++11)
include_directories(${LLVM_INCLUDE_DIR})
link_directories(${LLVM_LIBDIR})

ADD_EXECUTABLE (${CMAKE_PROJECT_NAME} main.cc)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
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
)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
  LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
  LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
  LLVMX86AsmPrinter # MC, Support, X86Utils
  LLVMX86Info # MC, Support, Target
  LLVMX86Utils # Core, Support
  LLVMipo
  LLVMScalarOpts
  LLVMInstCombine
  LLVMTransformUtils
  LLVMipa
  LLVMAnalysis
  LLVMTarget
  LLVMOption # Support
  LLVMMCParser # MC, Support
  LLVMMC # Object, Support
  LLVMObject # BitReader, Core, Support
  LLVMBitReader # Core, Support
  LLVMCore # Support
  LLVMSupport
)

INCLUDE (FindCurses)

TARGET_LINK_LIBRARIES (${CMAKE_PROJECT_NAME}
    pthread
    z
    dl
    ${CURSES_LIBRARIES}
)
