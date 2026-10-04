cmake_minimum_required(VERSION 3.16)

project(base64
    VERSION 0.1.0
    LANGUAGES C
)

include(CTest)

add_executable(base64
    src/base64.c
    ext/clic/src/clic.c
)

target_include_directories(base64 PRIVATE
    ext/clic/src
)

target_compile_definitions(base64 PRIVATE
    CLIC_NAME="base64"
    CLIC_DESCRIPTION="Encode/decode data in base64 format"
    CLIC_VERSION="v${PROJECT_VERSION}"
)

target_compile_options(base64 PRIVATE
    -Wall
    -Wextra
    -Wshadow
    -Wconversion
    -Wpedantic
    -Werror
)

set_target_properties(base64 PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)

if(BUILD_TESTING)
    function(add_encode_text_test name input expected_output)
        add_test(
            NAME ${name}
            COMMAND ${CMAKE_COMMAND}
                "-DBASE64_EXECUTABLE=$<TARGET_FILE:base64>"
                "-DINPUT_MODE=text"
                "-DINPUT=${input}"
                "-DEXPECTED_OUTPUT=${expected_output}"
                -P ${CMAKE_CURRENT_SOURCE_DIR}/test/run_encode_test.cmake
        )
    endfunction()

    function(add_encode_binary_test name input expected)
        add_test(
            NAME ${name}
            COMMAND ${CMAKE_COMMAND}
                "-DBASE64_EXECUTABLE=$<TARGET_FILE:base64>"
                "-DINPUT_MODE=file"
                "-DINPUT=${CMAKE_CURRENT_SOURCE_DIR}/test/input/${input}"
                "-DEXPECTED_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/expected/${expected}"
                -P ${CMAKE_CURRENT_SOURCE_DIR}/test/run_encode_test.cmake
        )
    endfunction()

    add_encode_text_test(encode_text_empty "" "")
    add_encode_text_test(encode_text_f "f" "Zg==")
    add_encode_text_test(encode_text_fo "fo" "Zm8=")
    add_encode_text_test(encode_text_foo "foo" "Zm9v")
    add_encode_text_test(encode_text_foob "foob" "Zm9vYg==")
    add_encode_text_test(encode_text_fooba "fooba" "Zm9vYmE=")
    add_encode_text_test(encode_text_foobar "foobar" "Zm9vYmFy")

    add_encode_binary_test(encode_binary_no_padding no_padding.bin no_padding.txt)
    add_encode_binary_test(encode_binary_two_unused_bits two_unused_bits.bin two_unused_bits.txt)
    add_encode_binary_test(encode_binary_four_unused_bits four_unused_bits.bin four_unused_bits.txt)
endif()
