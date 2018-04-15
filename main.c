#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "coder.h"

const char *argp_program_version = "morseconv 0.1";
static char doc[] = "Encrypts and decrypts message using Morse code. \"-\" stands for long signal, \".\" stands for short signal.";
static char args_doc[] = "[STRING...] [-v]";
static struct argp_option options[] = {
    { "encrypt", 'e', "STRING", 0, "Encrypts string provided and prints the output."},
    { "decrypt", 'd', "STRING", 0, "Decrypts string provided and prints the plain text."},
    { 0 }
};

struct arguments {
    enum {
        ENCRYPT_MODE,
        DECRYPT_MODE
        } mode;

    char* msg;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
        case 'e':
        arguments->mode = ENCRYPT_MODE;
        arguments->msg = arg;
        break;

        case 'd':
        arguments->mode = DECRYPT_MODE;
        arguments->msg = arg;
        break;

        case ARGP_KEY_ARG:
        return 0;

        default: return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main( int argc, char* argv[] )
{
    struct arguments arguments;
    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    if( arguments.mode == ENCRYPT_MODE ) {
        char* out = encode( arguments.msg );

        printf( "%s\n", out );
    } else if( arguments.mode == DECRYPT_MODE ) {
        printf( "%s\n", decode( arguments.msg ) );
    }

    return 0;
}
