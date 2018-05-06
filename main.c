#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "coder.h"

struct arguments {
    enum {
        NOT_SET,
        ENCRYPT_MODE,
        DECRYPT_MODE
        } mode;

    char* msg;
};

int main( int argc, char* argv[] ) {
    int c;
    while( 1 ) {
        static struct option options[] = {
            // MODE OPTIONS
            {"encode", required_argument, 0, 'e' },
            {"decode", required_argument, 0, 'd' },
            
            // ADDITIONAL OPTIONS
            {"matrix", required_argument, 0, 'm' },
            {"inspace", required_argument, 0, 's' },
            {"outspace", required_argument, 0, 'S' },
            {0, 0, 0, 0}
        };

        int option_index = 0;

        c = getopt_long( argc, argv, "e:d:m:s:S:", options, &option_index );

        if( c == -1 ) {
            break;
        }

        switch( c ) {
            case 0:
            if( options[ option_index ].flag != 0 ) {
                break;
            }

            case 'e':
            arguments.mode ? arguments.mode = ENCRYPT_MODE : exit( 1 );
            break;

            case 'd':
            arguments.mode ? arguments.mode = DECRYPT_MODE : exit( 1 );
            break;

            case 'm':
            char* user_matrix;
            strcpy( user_matrix, optarg );
            
        }
    }
    return 0;
}