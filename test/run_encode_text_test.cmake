if(NOT DEFINED BASE64_EXECUTABLE)
    message(FATAL_ERROR "BASE64_EXECUTABLE is required")
endif()

if(NOT DEFINED INPUT)
    message(FATAL_ERROR "INPUT is required")
endif()

if(NOT DEFINED EXPECTED_OUTPUT)
    message(FATAL_ERROR "EXPECTED_OUTPUT is required")
endif()

execute_process(
    COMMAND "${BASE64_EXECUTABLE}" encode "${INPUT}" --text
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
