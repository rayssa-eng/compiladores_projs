
%{
// Código em c/c++

#include

using namespace std;

enum TOKEN { ID = 256 };

%}


%%
 // Comentário começando na segunda coluna

[A-Za-z_][A-Za-z_0-9]* { cout << yytext << endl;
                         return ID; }

%%

// Funções auxiliares

int main() {
  int token = yylex();

  while( token != 0 ) {
    cout << "Valor: " << token << endl;
    token = yylex();
  }
}
