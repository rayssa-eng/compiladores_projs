%{
// Código em c/c++

#include <iostream>

using namespace std;

string lexema;

/* enum TOKEN { _ID = 256, _FOR, _IF, _INT, _FLOAT, _MAIG, _MEIG, _IG, _DIF, _STRING, _STRING2, _COMENTARIO, _EXPR }; */

#include <string>
#include <algorithm>

std::string removeDoubleQuotes(std::string str) {
    std::string stringOp = str;

    if (stringOp.front() == '"' && stringOp.back() == '"') {
        stringOp = stringOp.substr(1, stringOp.length() - 2);
    }

    return stringOp;
}

std::string removeDoubleSingleQuotes(std::string str) {
    std::string originalString = str;
    std::string resultString;
    char nonChar = '\0';

    for (char c: originalString) {
        if (!(c == '\'' && nonChar == c)) {
            resultString += c;
        }
        nonChar = c;
    }
    return resultString;
}


std::string treatString(std::string str) {
    std::string newString = removeDoubleQuotes(str);
    newString = removeDoubleSingleQuotes(newString);

    return newString;
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

\"([^\"\\]|\\.)*\" { lexema = treatString(yytext); return _STRING; }

\'([^\'\\]|\\.)*\' { lexema = treatString(yytext); return _STRING; }



{WS}	{ /* ignora espaços, tabs e '\n' */ } 

.   { lexema = yytext; return *yytext;
    /* Essa deve ser a última regra. Dessa forma qualquer caractere isolado será retornado pelo seu código ascii. */ 
}

%%

/* Não coloque nada aqui - a função main é automaticamente incluída na hora de avaliar e dar a nota. */



