%{
// Código em c/c++

#include <stdio.h>


char* lexema;

enum TOKEN { ID = 256, NUM, FOR, MENOR_IGUAL };

%}

DIGITO  [0-9]
LETRA   [A-Za-z]
NUM     {DIGITO}+
UNDERLINE   "_"
ID      ({LETRA}|{UNDERLINE})({LETRA}|{DIGITO}|{UNDERLINE})*


%%

[ \n\r\t]   { }


  /* Todas as palavras reservadas devem aparecer antes do padrão do ID */
"for"                  { lexema = yytext; return FOR; }
"<="                   { lexema = yytext; return MENOR_IGUAL; }

({CIFRAO})?({LETRA}|{UNDERLINE})({LETRA}|{DIGITO}|{UNDERLINE})* { lexema = yytext; return _ID; }
({CIFRAO}){DIGITO}+({LETRA}|{DIGITO}|{UNDERLINE})?              { lexema = yytext; return _ID; }

{_INT}  { lexema = yytext; return _INT; }

{ID}                   { lexema = yytext; return ID; }
{NUM}                 { lexema = yytext; return NUM; }

  /* Trata todos os símbolos de um caracter usando o código ASCII */
.                      { lexema = yytext; return yytext[0]; }

%%

// Funções auxiliares

int main() {
  int token = yylex();

  while( token != 0 ) {
    printf("Valor: %d, lexema: %s", token, lexema);
    token = yylex();
  }
}