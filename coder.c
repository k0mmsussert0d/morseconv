#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSPACE 1
#define SPACE 3

char* numb( const char );
int slen( const char* );

char* encode( char* in ) {
    const char *alph[ 26 ] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--.."
    };

    char* res;
    if( in[ 0 ] == '\0' ) {
        res = malloc( 1 );
        res[ 0 ] = '\0';
        return res;
    } else {
        res = malloc( strlen( in ) * 5 + slen( in ) * SPACE );
    }

    int i = 0, j;
    char* ptr = res;
    while( in[ i ] != '\0' ) {
        if( isalnum( in[ i ] ) || isspace( in[ i ] ) ) {
            if( isalpha( in[ i ] ) ) {
                char ref = toupper( in[ i ] );
                const char* buffer = alph[ ref - 'A' ];
                strcpy( ptr, buffer );
                ptr += strlen( buffer );
            } else if( isdigit( in[ i ] ) ) {
                const char* buffer = numb( in[ i ] );
                strcpy( ptr, buffer );
                ptr += strlen( buffer );
            } else if( isspace( in[ i ] ) ) {
                for( j = 0; j < SPACE; ++j ) {
                    *ptr++ = ' ';
                }
            }

            if( in[ i + 1 ] != '\0' && !isspace( in[ i + 1 ] ) ) {
                for( j = 0; j < INSPACE; ++j ) {
                    *ptr++ = ' ';
                }
            }
            ++i;
        } else {
            printf( "Napotkano niedozwolony znak: %c\nPrzerywam działanie!\n", in[ i ] );
            res[ 0 ] = '\0';
            return res;
        }
    }

    return res;
}

char* decode( char* in ) {
    char matrix[] = "%TEMNAIOGKDWRUS-.QZYCXBJP%L-FVH09%8%%%7%%%%%%%61%%%%%%%2%%%3%45";

    int len = slen( in );

    if( !len ) {
        char* res = malloc( 1 );
        res[ 0 ] = '\0';
        return res;
    }

    char* res = malloc( len + 2 );

    int i = 0, j = 0, k = 0;
    while( in[ i ] != '\0' ) {
        k = 0;
        while( in[ i ] != ' ' && in[ i ] != '\0' ) {
            if( in[ i ] == '-' ) {
                k = k * 2 + 1;
            } else {
                k = k * 2 + 2;
            }
            ++i;
        }
        printf( "%d %c\n", k, matrix[ k ] );
        if( k > 62 || matrix[ k ] == '%' ) {
            printf( "Napotkano niepoprawny znak!\n" );
            res[ 0 ] = '\0';
            return res;
        } else {
            res[ j++ ] = matrix[ k ];
        }
        ++i;
    }
    res[ j ] = '\0';

    return res;
}

char* numb( const char in ) {
    char* res = malloc( 6 );

    int i, j;
    const int lim = in - '0';
    if( lim <= 5 && lim >= 0 ) {
        for( i = 1, j = 0; i <= lim; ++i ) {
            res[ j++ ] = '.';
        }
        for( ; i <= 5; ++i ) {
            res[ j++ ] = '-';
        }
    } else {
        for( i = 1, j = 0; i <= lim - 5; ++i ) {
            res[ j++ ] = '-';
        }
        for( ; i <= 5; ++i ) {
            res[ j++ ] = '.';
        }
    }

    res[ j ] = '\0';

    return res;
}

int slen( const char* s ) {
    int i, len;
    for( i = 0; s[ i ] != '\0'; ++i ) {
        if( s[ i ] == ' ' ) {
            ++len;
        }
    }

    return len;
}
