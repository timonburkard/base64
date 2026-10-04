/*** Includes ****************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "clic.h"

/*** Defines *****************************************************************/

#define CHUNK_SIZE 3 // LCM(6, 8) = 24 bits = 3 bytes

static const char* BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/*** Function Declarations ***************************************************/

clic_err_t encode(clic_res_t* result);
clic_err_t decode(clic_res_t* result);
void       encode_as_base64(const uint8_t* input, size_t input_length);

/*** CLIC ********************************************************************/

enum {
    ARG_ID_INPUT = 0,
};

static const clic_arg_t arguments[] = {
    [ARG_ID_INPUT] = {
        .type        = CLIC_ARG_POSITIONAL,
        .required    = true,
        .names       = NULL,
        .value_name  = "FILE",
        .description = "File to hex dump or '-' for stdin",
    },
};

static const char* const encode_names[] = {"encode", NULL};
static const char* const decode_names[] = {"decode", NULL};

static const clic_cmd_t commands[] = {
    {
        .names       = encode_names,
        .description = "encode something as base64",
        .function    = encode,
        .argc        = (uint8_t)(sizeof(arguments) / sizeof(arguments[0])),
        .argv        = arguments,
    },
    {
        .names       = decode_names,
        .description = "decode something from base64",
        .function    = decode,
        .argc        = (uint8_t)(sizeof(arguments) / sizeof(arguments[0])),
        .argv        = arguments,
    },
};

/*** Main ********************************************************************/

int main(int argc, char** argv)
{
    return (int)clic_parse(
        (uint8_t)(sizeof(commands) / sizeof(commands[0])),
        commands,
        argc,
        (const char* const*)argv);
}

/*** Function Definitions ****************************************************/

clic_err_t encode(clic_res_t* result)
{
    size_t  read_bytes;
    FILE*   file;
    uint8_t input[CHUNK_SIZE];

    file = fopen(result->argv[ARG_ID_INPUT], "rb");

    if (file == NULL) {
        fprintf(stderr, "Failed to open input file: %s\n", result->argv[ARG_ID_INPUT]);
        return CLIC_ERR_GENERAL;
    }

    do {
        read_bytes = fread(input, 1, CHUNK_SIZE, file);

        if (read_bytes == 0) {
            if (ferror(file)) {
                fprintf(stderr, "Error reading input file: %s\n", result->argv[ARG_ID_INPUT]);
                fclose(file);
                return CLIC_ERR_GENERAL;
            }

            fclose(file);
            return CLIC_ERR_OK;
        }

        encode_as_base64(input, read_bytes);
    } while (read_bytes == CHUNK_SIZE);

    fclose(file);
    return CLIC_ERR_OK;
}

void encode_as_base64(const uint8_t* input, size_t input_length)
{
    if (input_length == 0) {
        return;
    }

    printf("%c", BASE64_CHARS[input[0] >> 2]);

    if (input_length == 1) {
        printf("%c", BASE64_CHARS[(input[0] & 0x03) << 4]);
        printf("==");
    } else if (input_length == 2) {
        printf("%c", BASE64_CHARS[((input[0] & 0x03) << 4) | (input[1] >> 4)]);
        printf("%c", BASE64_CHARS[(input[1] & 0x0F) << 2]);
        printf("=");
    } else if (input_length == 3) {
        printf("%c", BASE64_CHARS[((input[0] & 0x03) << 4) | (input[1] >> 4)]);
        printf("%c", BASE64_CHARS[((input[1] & 0x0F) << 2) | (input[2] >> 6)]);
        printf("%c", BASE64_CHARS[input[2] & 0x3F]);
    } else {
        printf("Invalid input length for base64 encoding: %llu\n", (unsigned long long int)(input_length));
    }
}

clic_err_t decode(clic_res_t* result)
{
    (void)result;

    return CLIC_ERR_OK;
}
