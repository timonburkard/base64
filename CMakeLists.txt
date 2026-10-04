cmake_minimum_required(VERSION 3.16)

project(base64
    VERSION 0.1.0
    LANGUAGES C
)

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
