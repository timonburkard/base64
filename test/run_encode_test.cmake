if(NOT DEFINED BASE64_EXECUTABLE)
    message(FATAL_ERROR "BASE64_EXECUTABLE is required")
endif()

if(NOT DEFINED INPUT)
    message(FATAL_ERROR "INPUT is required")
endif()

if(NOT DEFINED INPUT_MODE)
    message(FATAL_ERROR "INPUT_MODE is required")
endif()

if(DEFINED EXPECTED_FILE)
    if(NOT EXISTS "${EXPECTED_FILE}")
        message(FATAL_ERROR "Expected output file does not exist: ${EXPECTED_FILE}")
    endif()

    file(READ "${EXPECTED_FILE}" EXPECTED_OUTPUT)
    string(REGEX REPLACE "\r?\n$" "" EXPECTED_OUTPUT "${EXPECTED_OUTPUT}")
elseif(NOT DEFINED EXPECTED_OUTPUT)
    message(FATAL_ERROR "EXPECTED_OUTPUT or EXPECTED_FILE is required")
endif()

set(input_mode_arguments)

if(INPUT_MODE STREQUAL "text")
    list(APPEND input_mode_arguments --text)
elseif(NOT INPUT_MODE STREQUAL "file")
    message(FATAL_ERROR "INPUT_MODE must be 'text' or 'file'")
endif()

execute_process(
    COMMAND "${BASE64_EXECUTABLE}" encode "${INPUT}" ${input_mode_arguments}
    RESULT_VARIABLE actual_exit
    OUTPUT_VARIABLE actual_output
    ERROR_VARIABLE actual_error
)

if(NOT actual_exit EQUAL 0)
    message(FATAL_ERROR
        "Unexpected exit code: ${actual_exit}\n"
        "Expected exit code: 0\n"
        "stdout:\n${actual_output}\n"
        "stderr:\n${actual_error}"
    )
endif()

if(NOT actual_error STREQUAL "")
    message(FATAL_ERROR "Unexpected stderr:\n${actual_error}")
endif()

if(NOT actual_output STREQUAL EXPECTED_OUTPUT)
    message(FATAL_ERROR
        "Unexpected stdout.\n"
        "Expected:\n---\n${EXPECTED_OUTPUT}---\n"
        "Actual:\n---\n${actual_output}---"
    )
endif()
