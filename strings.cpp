#include <stdio.h>
#include <string>

using namespace std;

enum TOKEN { MENOR_IGUAL = 256, MAIOR_IGUAL, DIFERENTE, ID, NUM };

const int MAX_ID = 1023;
string lexema;

int is_digit( int ch ) {
    return ch >= '0' && ch <= '9';
}

int is_alpha( int ch ) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

int is_alnum( int ch ) {
    return is_alpha( ch ) || is_digit( ch );
}

int is_space( int ch ) {
    return ch == ' ' || ch == '\n' || ch == '\t';
}

int next_token() {
    static int la = ' ';

    lexema = "";

    // Desconsiderar espaços em branco.
    while( is_space( la ) )
        la = getchar();

    if( is_alpha( la ) ) {
        lexema += la;
        la = getchar();

        while( is_alnum( la ) ) {
            lexema += la;
            la = getchar();
        }

        return ID;
    }
    else if( is_digit( la ) ) {
        lexema += la;
        la = getchar();
        while( is_digit( la ) ) {
            lexema += la;
            la = getchar();
        }

        return NUM;
    }
    else switch( la ) {
            case '<': {
                lexema += la;
                la = getchar();

                if( la == '=' ) {
                    lexema += la;
                    la = getchar();
                    return MENOR_IGUAL;
                }

                if( la == '>' ) {
                    lexema += la;
                    la = getchar();
                    return DIFERENTE;
                }

                return '<';
            }

            case '>': {
                lexema += la;
                la = getchar();

                if( la == '=' ) {
                    lexema += la;
                    la = getchar();
                    return MAIOR_IGUAL;
                }

                return '>';
            }

            case '=' :
            case '+' :
            case '-' :
            case '*' :
            case '/' :
            case '(' :
            case ')' : {
                lexema += la;
                la = getchar();
                return lexema[0];
            }

        }

    return EOF;
}

int main( int argc, char* argv[] ) {
    int token;

    while( (token = next_token()) != EOF )
        printf( "Lido: %d [%s]\n", token, lexema.c_str() );

    return 0;
}