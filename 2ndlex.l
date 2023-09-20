%{
// Código em c/c++

#include <iostream>

using namespace std;

string lexema;

enum TOKEN { ID = 256, NUM, FOR, MENOR_IGUAL };

%}


%%

[ \n\r\t]   { }


  /* Todas as palavras reservadas devem aparecer antes do padrão do ID */
"for"                  { lexema = yytext; return FOR; }
"<="                   { lexema = yytext; return MENOR_IGUAL; }

[A-Za-z_][A-Za-z_0-9]* { lexema = yytext; return ID; }
[0-9]+                 { lexema = yytext; return NUM; }

  /* Trata todos os símbolos de um caracter usando o código ASCII */
.                      { lexema = yytext; return yytext[0]; }

%%

// Funções auxiliares

int main() {
  int token = yylex();

  while( token != 0 ) {
    cout << "Valor: " << token << ", lexema: " << lexema << endl;
    token = yylex();
  }
}
