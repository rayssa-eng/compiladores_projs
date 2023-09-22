%{
// Código em c/c++

#include <iostream>

using namespace std;

string lexema;

/* enum TOKEN { _ID = 256, _FOR, _IF, _INT, _FLOAT, _MAIG, _MEIG, _IG, _DIF, _STRING, _STRING2, _COMENTARIO, _EXPR }; */

#include <string>
#include <algorithm>

std::string treatDoubleQuotes(std::string str) {
    std::string lexema = yytext;
    lexema = lexema.substr(1, lexema.length() - 2);

    size_t pos = lexema.find("\\\"");
    while (pos != std::string::npos) {
        lexema.replace(pos, 2, "\"");
        pos = lexema.find("\\\"", pos + 1);
    }
    return lexema;
}

std::string treatSingleQuotes(std::string str) {
    std::string lexema = yytext;
    lexema = lexema.substr(1, lexema.length() - 2);

    size_t pos = lexema.find("\\'");
    while (pos != std::string::npos) {
        lexema.replace(pos, 2, "'");
        pos = lexema.find("\\'", pos + 1);
    }
    return lexema;
}

std::string treatBackticks(std::string str) {
    std::string lexema = yytext;
    lexema = lexema.substr(1, lexema.length() - 2);

    return lexema;
}


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
"/*"([^*]|[^/][*]*[^*/])*"*/" { lexema = yytext; return _COMENTARIO; }
"//".*$                        { lexema = yytext; return _COMENTARIO; }

[fF][oO][rR] { lexema = yytext; return _FOR; }
[iI][fF]     { lexema = yytext; return _IF; }

({CIFRAO})?({LETRA}|{UNDERLINE})({LETRA}|{DIGITO}|{UNDERLINE})* { lexema = yytext; return _ID; }
({CIFRAO})({DIGITO}*)({LETRA}|{DIGITO}|{UNDERLINE})?              { lexema = yytext; return _ID; }

({CIFRAO}{CIFRAO}|{CIFRAO}{UNDERLINE}{CIFRAO}|{LETRA}*{CIFRAO}) { cout << "Erro: Identificador invalido: " << yytext << endl; }

{_INT}  { lexema = yytext; return _INT; }

({_INT})\.({_INT})([eE][+-]?({_INT}))? { lexema = yytext; return _FLOAT; }
({_INT})[eE][+-]?({_INT})              { lexema = yytext; return _FLOAT; }

(>=) { cout << _MAIG << " " << yytext << endl; }
(<=) { cout << _MEIG << " " << yytext << endl; }
(==) { cout << _IG << " " << yytext << endl; }
(!=) { cout << _DIF << " " << yytext << endl; }

\"(\\.|[^\"])*\" { lexema = treatDoubleQuotes(yytext); return _STRING; }

\'(\\.|[^\'])*\' { lexema = treatSingleQuotes(yytext); return _STRING; }

\`[^\`]+\` { lexema = treatBackticks(yytext); return _STRING2; }

({CIFRAO})\{[^\}]+\} { lexema = yytext; return _EXPR; }

{WS}	{ /* ignora espaços, tabs e '\n' */ }

.   { lexema = yytext; return *yytext;
    /* Essa deve ser a última regra. Dessa forma qualquer caractere isolado será retornado pelo seu código ascii. */
}

%%

/* Não coloque nada aqui - a função main é automaticamente incluída na hora de avaliar e dar a nota. */



