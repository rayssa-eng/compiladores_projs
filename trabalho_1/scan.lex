%{
// Código em c/c++

#include <iostream>

using namespace std;

string lexema;

/* enum TOKEN { _ID = 256, _FOR, _IF, _INT, _FLOAT, _MAIG, _MEIG, _IG, _DIF, _STRING, _STRING2, _COMENTARIO, _EXPR }; */



%}

/* Coloque aqui definições regulares */
DIGITO      [0-9]
LETRA       [A-Za-z]
_INT         {DIGITO}+
CIFRAO      "$"
UNDERLINE   "_"
WS	        [ \t\n]
MAIG [>=]


%%
    /* Padrões e ações. Nesta seção, comentários devem ter um tab antes */
[fF][oO][rR] { lexema = yytext; return _FOR; }
[iI][fF]     { lexema = yytext; return _IF; }

({CIFRAO})?({LETRA}|{UNDERLINE})({LETRA}|{DIGITO}|{UNDERLINE})* { lexema = yytext; return _ID; }
({CIFRAO}){DIGITO}+({LETRA}|{DIGITO}|{UNDERLINE})?              { lexema = yytext; return _ID; }

{_INT}  { lexema = yytext; return _INT; }

({_INT})\.({_INT})([eE][+-]?({_INT}))? { lexema = yytext; return _FLOAT; }
({_INT})[eE][+-]?({_INT})              { lexema = yytext; return _FLOAT; }

>= { cout << _MAIG << " " << yytext << endl; }
    /* [<=] { lexema == yytext; return _MEIG; }
    [==] { lexema == yytext; return _IG; }
    [!=] { lexema == yytext; return _DIF; } */




{WS}	{ /* ignora espaços, tabs e '\n' */ } 

.   { lexema = yytext; return *yytext;
    /* Essa deve ser a última regra. Dessa forma qualquer caractere isolado será retornado pelo seu código ascii. */ 
}

%%

/* Não coloque nada aqui - a função main é automaticamente incluída na hora de avaliar e dar a nota. */



