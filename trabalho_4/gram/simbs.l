%{
int token( int tk );
char *trim(char *str);
vector<string> tokeniza(const string& str);
%}

D  	    [0-9]
L   	[A-Za-z_]
INT	    {D}+
DOUBLE  {D}+"."{D}+([Ee][+\-]?{D}+)?
ID      {L}({L}|{D})*
BOOLEAN    "true"|"false"

%%

"\t"       { coluna += 4; }
" "        { coluna++; }
"\n"	   { linha++; coluna = 0; }

{DOUBLE}   { return token( CDOUBLE ); }
{INT}	   { return token( CINT ); }
{BOOLEAN}  { return token( BOOL ); }

"{}"       { return token( OBJECT ); }
"&&"	   { return token( AND ); }
"||"	   { return token( OR ); }
"<="	   { return token( ME_IG ); }
">="	   { return token( MA_IG ); }
"!="	   { return token( DIF ); }
"=="	   { return token( IGUAL ); }

"+="       { return token( MAIS_IGUAL ); }
"++"       { return token( MAIS_MAIS ); }

"let"      { return token( LET ); }
"const"    { return token( CONST ); }
"var"      { return token( VAR ); }
"if"       { return token( IF ); }
"else"     { return token( ELSE ); }

"for"      { return token( FOR ); }
"while"    { return token( WHILE ); }
"function" { return token( FUNCTION ); }
"return"   { return token( RETURN ); }
{ID}       { return token( ID ); }

"\""[^\"]*"\"" { yylval.c = vector<string>{ string(yytext + 1, yyleng - 2) }; return token(CSTRING); } { yylval.c = vector<string>{ string(yytext + 1, yyleng - 2) }; return token(CSTRING); }
"'"([^']*)"'" { yylval.c = vector<string>{ string(yytext + 1, yyleng - 2) }; return token(CSTRING); }

"asm{".*"}"  {  char *lexema = trim(yytext);  
                yylval.c = tokeniza( lexema );
                coluna += strlen( yytext ); 
                return ASM; }

.          { return token( *yytext ); }

%%

char *trim(char *str) {
    // Skip the first four characters
    int i;
    for (i = 0; i < 4 && str[i] != '\0'; ++i) {
        // Para avancar o ponteiro
    }

    // Rearranjar os caracteres
    memmove(str, str + i, strlen(str + i) + 1);

    int len = strlen(str);

    if (len > 0) {
        str[len - 1] = '\0';
    }

    return str;
}

vector<string> tokeniza(const string& str) {
    vector<string> str_vector;
    size_t start = 0;
    size_t end = str.find(' ');

    while (end != std::string::npos) {
        str_vector.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(' ', start);
    }

    // Adiciona ultimo token
    str_vector.push_back(str.substr(start));

    return str_vector;
}

int token( int tk ) {  
  yylval.c = vector<string>{ yytext };
  coluna += strlen( yytext ); 
  
  yylval.linha = linha;
  yylval.coluna = coluna;

  return tk;
}