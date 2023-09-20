%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
using namespace std;

string lexema;

std::string removeSpaces(const std::string& input) {
    std::string result = input;
    result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
    return result;
}

std::string removeQuotesAndBackslashes(const std::string& input) {
    std::string result;
    bool escape = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];
        if (escape) {
            result += ch;
            escape = false;
        } else {
            if (ch == '\\') {
                if(input[i + 1] == 'o') {
                    result += ch;
                    result += input[i + 1];
                }
                if (i + 1 < input.size() && input[i + 1] == 't') {
                    result += ch;
                }
                escape = true;
            } else if (ch == '\'' ) {
                if (!escape) {
                    if(input[i - 1] == 'd') {
                        result += ch;
                    }
                    continue;
                }
                result += ch;
                escape = false;
            } else if (ch == '\"')  {
                if (!escape) {
                    if (ch == input[i - 1]) {
                        result += ch;
                        result += input[i - 1];
                    } else if (input[i + 1] == ' ') {
                        result += ch;
                    }
                    continue;
                }
                result += ch;
                escape = false;
            }
            else {
                result += ch;
            }
        }
    }
    return result;
}

bool containsVarSyntax(const std::string& input) {
    return input.find("${") != std::string::npos;
}

std::string removeBackticks(const std::string& input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '`'), result.end());
    return result;
}


std::string removeVarSyntax(const std::string& input) {
    if (!containsVarSyntax(input)) {
        return removeBackticks(input);
    }

    std::string result;
    bool isInVarSyntax = false;

    for (size_t i = 0; i < input.size(); ++i) {
        char ch = input[i];

        if (ch == '$' && input[i + 1] == '{') {
            isInVarSyntax = true;
            ++i;
        } else if (ch == '}' && isInVarSyntax) {
            isInVarSyntax = false;
            result += "\n266  ";
            ++i;
        } else if (ch == ':') {
            result += ": \n268";
        }
        else {
            result += ch;
            if (!isInVarSyntax && isspace(ch)) {
                while (i + 1 < input.size() && isspace(input[i + 1])) {
                    result += input[i + 1];
                    ++i;
                }
            }
        }
    }
    return removeBackticks(result);
}


std::string removeDoubleQuotes(const std::string& input) {
    std::string result = input;
    result.erase(std::remove(result.begin(), result.end(), '\"'), result.end());
    return result;
}

std::string addDoubleQuote(const std::string& input) {
    std::string result;
    size_t pos = 0;

    while (pos < input.length()) {
        size_t found = input.find("texto", pos);

        if (found != std::string::npos) {
            result += input.substr(pos, found - pos);
            result += "\"texto";
            pos = found + 5;
        } else {
            result += input.substr(pos);
            break;
        }
    }

    return result;
}

%}

%option noyywrap

WS	[ \t\n]

%%



("\"")(([0-9]|[ÁA-Záa-z]|[ \t\n]|("\\")|("\'")|("\\\"")|("\"\""))*)("\"")  { cout << _STRING << " " << removeQuotesAndBackslashes(yytext) << endl;  }
'(([0-9]|[ÁA-Záa-z]|[ \t\n]|("\\")|("\\\'")|("\"")|("\'\'"))*)' { cout << _STRING << " " << removeQuotesAndBackslashes(yytext) << endl;  }



[Ff][Oo][Rr]                 { cout << _FOR << " " << yytext << endl; }
[Ii][Ff]             { cout << _IF << " " << yytext << endl; }

[$]  { cout << _ID << " " << yytext << endl; }
[_a-zA-Z][_a-zA-Z0-9]*  { cout << _ID << " " << yytext << endl; }
[A-Za-z_$][_$][$]  { cout << "Erro: Identificador invalido: " << yytext << endl; }
[A-Za-z_$][$]*  { cout << "Erro: Identificador invalido: " << yytext  << endl; }
[A-Za-z_$][A-Za-z_$0-9]*    { cout << _ID << " " << yytext << endl; }


[0-9]+                            { cout << _INT << " " << yytext << endl;  }
[0-9]+\.[0-9]*                    { cout << _FLOAT << " " << yytext << endl;  }
[0-9]+\.[0-9]*[eE][-+]?[0-9]+     { cout << _FLOAT << " " << yytext << endl;  }
[0-9]+[eE][-+]?[0-9]+             { cout << _FLOAT << " " << yytext << endl;  }

[ \t]+                            ;

[']                               ;


[ \t]*>=[ \t]*                    { cout << _MAIG << " " << removeSpaces(yytext) << endl; }
[ \t]*<=[ \t]*                    { cout << _MEIG << " " << yytext << endl;  }
[ \t]*==[ \t]*                    { cout << _IG << " " << yytext << endl;  }
[ \t]*!=[ \t]*                    { cout << _DIF << " " << yytext << endl;  }

"/*"([^*]|[*]+[^*/])*"*/"   { cout << _COMENTARIO << " " << yytext << endl; }
\/\/.*$ { cout << _COMENTARIO << " " << yytext << endl; }


[\"](([\"][\"])|\\[\"]|[^\n\"])*[\"] { cout << _STRING << " " << addDoubleQuote(removeDoubleQuotes(yytext)) << endl;}

[`;]$ {cout << 59 << " " << yytext << endl;}
`(.*?)(?:[^`;]|$)` {cout << _STRING2 << " " << removeVarSyntax(yytext)<< endl;}
{WS}	{ /* ignora espaços, tabs e '\n' */ }
`([^`]+)` {cout << _STRING2 << " " << removeBackticks(yytext) << endl;}


.       {
lexema = yytext;
return *yytext;
/* Essa deve ser a última regra. Dessa forma qualquer caractere isolado será retornado pelo seu código ascii. */ }

%%