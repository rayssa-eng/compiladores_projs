%{
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int linha = 1, coluna = 0;
// string lexema; 

struct Atributos {
  vector<string> c; // Código

  int linha = 0, coluna = 0;

  // Só para argumentos e parâmetros
  int n_args = 0;
  int rmv_from_stack = 1; 
  
  // Só para valor default de argumento        
  vector<string> valor_default; 

  void clear() {
    c.clear();
    valor_default.clear();
    linha = 0;
    coluna = 0;
    n_args = 0;
    rmv_from_stack = 1;
  }
};

enum TipoDecl { Let = 1, Const, Var };
map<TipoDecl, string> nomeTipoDecl = { 
  { Let, "let" }, 
  { Const, "const" }, 
  { Var, "var" }
};

struct Simbolo {
  TipoDecl tipo;
  int linha;
  int coluna;
};

int in_func = 0;

// Tabela de símbolos - agora é uma pilha
vector< map< string, Simbolo > > ts = { map< string, Simbolo >{} }; 
vector<string> funcoes;

vector<string> declara_var( TipoDecl tipo, string nome, int linha, int coluna );
void checa_retorno( int in_func );
void checa_simbolo( string nome, bool modificavel );


#define YYSTYPE Atributos

extern "C" int yylex();
int yyparse();
void yyerror(const char *);

vector<string> concatena( vector<string> a, vector<string> b ) {
  a.insert( a.end(), b.begin(), b.end() );
  return a;
}

vector<string> operator+( vector<string> a, vector<string> b ) {
  return concatena( a, b );
}

vector<string> operator+( vector<string> a, string b ) {
  a.push_back( b );
  return a;
}

vector<string> operator+( string a, vector<string> b ) {
  return vector<string>{ a } + b;
}

// bool operator!=(vector<string> a, vector<string> b) {
//   return a != b;
// }

vector<string> resolve_enderecos( vector<string> entrada ) {
  map<string,int> label;
  vector<string> saida;
  for( int i = 0; i < entrada.size(); i++ ) 
    if( entrada[i][0] == ':' ) 
        label[entrada[i].substr(1)] = saida.size();
    else
      saida.push_back( entrada[i] );
  
  for( int i = 0; i < saida.size(); i++ ) 
    if( label.count( saida[i] ) > 0 )
        saida[i] = to_string(label[saida[i]]);
    
  return saida;
}

string gera_label( string prefixo ) {
  static int n = 0;
  return prefixo + "_" + to_string( ++n ) + ":";
}

void print( vector<string> codigo ) {
  for( string s : codigo )
    cout << s << " ";
    
  cout << endl;  
}

%}

%token IF ELSE FOR WHILE LET CONST VAR FUNCTION ASM RETURN
%token ID CDOUBLE CSTRING CINT BOOL BLVAZIO SETA PARENTESES_FUNCAO CHAVES_FUNCAO
%token AND OR DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS

%right '=' SETA
%nonassoc IF ELSE IGUAL MAIS_IGUAL MAIS_MAIS MA_IG ME_IG DIF
%nonassoc '<' '>' 
%left AND OR
%left '+' '-'
%left '*' '/' '%'
%right '[' '(' '{'
%left '.'


%%

S : CMDs { print( resolve_enderecos( $1.c + "." + funcoes ) ); }
  ;

CMDs : CMDs CMD  { $$.c = $1.c + $2.c; };
     |           { $$.clear(); }
     ;
            
     
CMD : CMD_LET ';'
    | CMD_VAR ';'
    | CMD_CONST ';'
    | CMD_IF
    | CMD_WHILE
    | CMD_FUNC
    | RETURN E ';'
      { checa_retorno( in_func ); $$.c = $2.c + "'&retorno'" + "@" + "~"; }
    | RETURN OBJECT ';'
      { $$.c = $2.c + "'&retorno'" + "@" + "~"; }
    | CMD_FOR
    | E ASM ';' 	{ $$.c = $1.c + $2.c + "^"; }
    | E ';'
      { $1.rmv_from_stack ? $$.c = $1.c + "^" :  $$.c = $1.c; };
    | ';'
      { $$.clear(); };
    | '{' EMPILHA_TS CMDs '}'
      { ts.pop_back();
        $$.c = vector<string>{"<{"} + $3.c + vector<string>{"}>"};  }
    | BLVAZIO
      { $$.clear(); }
    ;

/* OBJECT : BLVAZIO ; */

EMPILHA_TS : { ts.push_back( map< string, Simbolo >{} ); } 
           ;
   
CMD_FUNC : FUNCTION ID { declara_var( Var, $2.c[0], $2.linha, $2.coluna ); } 
             '(' LISTA_ARGs ')' '{' { in_func++; } CMDs '}'
           { 
             string lbl_endereco_funcao = gera_label( "func_" + $2.c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             $$.c = $2.c + "&" + $2.c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + $5.c + $9.c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back(); 
             in_func--;
           }
         ;

         
LISTA_ARGs : ARGs
           | { ts.push_back( map< string, Simbolo >{}); $$.c.clear(); }
           ;
           
ARGs : ARGs ',' ARG  
       { // a & a arguments @ 0 [@] = ^ 
         declara_var( Let, $3.c[0], $3.linha, $3.coluna ); 
         $$.c = $1.c + $3.c + "&" + $3.c + "arguments" + "@" + to_string( $1.n_args )
                + "[@]" + "=" + "^"; 
         if( $3.valor_default.size() > 0 ) {
           string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
           $$.c = $$.c + $3.c + "@" + "undefined" + "@" + "!=" +
                 lbl_true + "?" + $3.c + $3.valor_default + "=" + "^" + 
                 lbl_fim_if + "#" +
                 definicao_lbl_true + definicao_lbl_fim_if
                 ;
         }
         $$.n_args = $1.n_args + $3.n_args; 
       }
     | ARG 
       { // a & a arguments @ 0 [@] = ^ 
         ts.push_back( map< string, Simbolo >{});
         declara_var( Let, $1.c[0], $1.linha, $1.coluna );
         $$.c = $1.c + "&" + $1.c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
         if( $1.valor_default.size() > 0 ) {
           string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
           $$.c = $$.c + $1.c + "@" + "undefined" + "@" + "!=" +
                 lbl_true + "?" + $1.c + $1.valor_default + "=" + "^" +
                 lbl_fim_if + "#" +
                 definicao_lbl_true + 
                 definicao_lbl_fim_if
                 ;
         }
         $$.n_args = $1.n_args; 
       }
     ;
     
ARG : ID 
      { $$.c = $1.c;      
        $$.n_args = 1;
        $$.valor_default.clear();
        // declara_var( Let, $1.c[0], $1.linha, $1.coluna ); 
      }
    | ID '=' E
      { // Código do IF
        $$.c = $1.c;
        $$.n_args = 1;
        $$.valor_default = $3.c;         
        // declara_var( Let, $1.c[0], $1.linha, $1.coluna ); 
      }
    ;
 
CMD_FOR : FOR '(' PRIM_E ';' E ';' E ')' CMD 
        { string lbl_fim_for = gera_label( "fim_for" );
          string lbl_condicao_for = gera_label( "condicao_for" );
          string lbl_comando_for = gera_label( "comando_for" );
          string definicao_lbl_fim_for = ":" + lbl_fim_for;
          string definicao_lbl_condicao_for = ":" + lbl_condicao_for;
          string definicao_lbl_comando_for = ":" + lbl_comando_for;
          
          $$.c = $3.c + definicao_lbl_condicao_for +
                 $5.c + lbl_comando_for + "?" + lbl_fim_for + "#" +
                 definicao_lbl_comando_for + $9.c + 
                 $7.c + "^" + lbl_condicao_for + "#" +
                 definicao_lbl_fim_for;
        }
        ;

PRIM_E : CMD_LET 
       | CMD_VAR
       | CMD_CONST
       | E  
         { $$.c = $1.c + "^"; }
       ;

CMD_LET : LET LET_VARs { $$.c = $2.c; }
        ;

LET_VARs : LET_VAR ',' LET_VARs { $$.c = $1.c + $3.c; } 
         | LET_VAR
         ;

LET_VAR : ID  
          { $$.c = declara_var( Let, $1.c[0], $1.linha, $1.coluna ); }
        | ID '=' E
          { 
            $$.c = declara_var( Let, $1.c[0], $1.linha, $1.coluna ) + 
                   $1.c + $3.c + "=" + "^"; }
        | ID '=' OBJECT
          { 
            $$.c = declara_var( Let, $1.c[0], $1.linha, $1.coluna ) + 
                   $1.c + $3.c + "=" + "^"; }
        ;
  
CMD_VAR : VAR VAR_VARs { $$.c = $2.c; }
        ;
        
VAR_VARs : VAR_VAR ',' VAR_VARs { $$.c = $1.c + $3.c; } 
         | VAR_VAR
         ;

VAR_VAR : ID  
          { $$.c = declara_var( Var, $1.c[0], $1.linha, $1.coluna ); }
        | ID '=' E
          {  $$.c = declara_var( Var, $1.c[0], $1.linha, $1.coluna ) + 
                    $1.c + $3.c + "=" + "^"; }
        ;
  
CMD_CONST: CONST CONST_VARs { $$.c = $2.c; }
         ;
  
CONST_VARs : CONST_VAR ',' CONST_VARs { $$.c = $1.c + $3.c; } 
           | CONST_VAR
           ;

CONST_VAR : ID '=' E
            { $$.c = declara_var( Const, $1.c[0], $1.linha, $1.coluna ) + 
                     $1.c + $3.c + "=" + "^"; }
           
          ;
  
CMD_IF : IF '(' E ')' CMD ELSE CMD
         { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            $$.c = $3.c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   $7.c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + $5.c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         };
        | IF '(' E ')' CMD
        {  string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            $$.c = $3.c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   lbl_fim_if + "#" +           // Código do False
                   definicao_lbl_true + $5.c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;}
       ;

CMD_WHILE : WHILE '(' E ')' CMD
            { string lbl_while_start = gera_label("while_start");
              string lbl_while_end = gera_label("while_end");
              string lbl_condicao_while = gera_label("while_true");
              string definicao_lbl_while_start = ":" + lbl_while_start;
              string definicao_lbl_while_end = ":" + lbl_while_end;
              string definicao_lbl_condicao_while = ":" + lbl_condicao_while;

              $$.c = definicao_lbl_condicao_while + $3.c +
                     lbl_while_start + "?" +
                     lbl_while_end + "#" +
                     definicao_lbl_while_start + $5.c +
                     lbl_condicao_while + "#" +
                     definicao_lbl_while_end
            ;
            }
          ;

LVALUEPROP : E '[' E ']'
              { $$.c = $1.c+ $3.c; }
           | E '.' ID  
              { $$.c = $1.c + $3.c; }
           | E '.' ID '[' E ']'
              { $$.c = $1.c + $3.c + "[@]" + $5.c; }
           ;

LISTA_PARAMs : PARAMs
           | { $$.clear(); }
           ;
             
PARAMs : PARAMs ',' E
       { $$.c = $1.c + $3.c;
         $$.n_args = $1.n_args + 1; }
     | E
       { $$.c = $1.c;
         $$.n_args = $1.n_args + 1; }
     ;

  E : ID '=' E 
    { if( !in_func ) checa_simbolo( $1.c[0], true ); $$.c = $1.c + $3.c + "="; }
  | ID '=' OBJECT
    { if( !in_func ) checa_simbolo( $1.c[0], true ); $$.c = $1.c + $3.c + "="; }
  | ID MAIS_MAIS
    { checa_simbolo( $1.c[0], true ); $$.c = $1.c + "@" + $1.c + $1.c + "@" + "1" + "+" + "=" + "^"; }
  | ID MAIS_IGUAL E
    { checa_simbolo( $1.c[0], true ); $$.c = $1.c + $1.c + "@" + $3.c + "+" + "="; }
  | LVALUEPROP '=' E
    { if( !in_func ) checa_simbolo( $1.c[0], true ); $$.c = $1.c + $3.c + "[=]"; }
  | LVALUEPROP MAIS_IGUAL E
    { checa_simbolo( $1.c[0], true ); $$.c = $1.c + $1.c + "[@]" + $3.c + "+" + "[=]"; }
  | E IGUAL E
    { $$.c = $1.c + $3.c + "=="; }
  | E DIF E     
    { $$.c = $1.c + $3.c + "!="; }
  | E '<' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '*' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '/' E
    { $$.c = $1.c + $3.c + $2.c; }
  | E '%' E
    { $$.c = $1.c + $3.c + $2.c; }
  | '-' E
    { $$.c = "0" + $2.c + $1.c; }
  | E '(' LISTA_PARAMs ')'
    {
      $$.c = $3.c + to_string( $3.n_args ) + $1.c + "$";
    } 
  | CDOUBLE
    { $$.c = $1.c; }
  | CINT
    { $$.c = $1.c; }
  | CSTRING
    { $$.c = $1.c; }
  | BOOL
    { $$.c = $1.c; }
  | ID
    { if( !in_func ) checa_simbolo( $1.c[0], false ); $$.c = $1.c + "@"; } 
  | LVALUEPROP 
    { if( !in_func ) checa_simbolo( $1.c[0], false ); $$.c = $1.c + "[@]"; }
  | ANONYM_FUNC  
  | ID_EMPILHA_TS SETA E 
    { 
      string lbl_endereco_funcao = gera_label( "func_" + $1.c[0] );
      string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
      
      $$.c = "{}" + vector<string>{ "'&funcao'" } + lbl_endereco_funcao + "[<=]";
      $$.rmv_from_stack = 0;
      funcoes = funcoes + definicao_lbl_endereco_funcao + $1.c + "&" + $1.c + 
                "arguments" + "@" + "0" + "[@]" + "=" + "^" + $3.c + 
                "'&retorno'" + "@"+ "~";
      in_func--;  
      ts.pop_back(); 
    }
  | '(' LISTA_ARGs PARENTESES_FUNCAO SETA E 
    { 
      string lbl_endereco_funcao = gera_label( "func_" );
      string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
      
      $$.c = vector<string>{ "{}" } + vector<string>{ "'&funcao'" } +
            lbl_endereco_funcao + vector<string>{ "[<=]" };
      $$.rmv_from_stack = 0;
      funcoes = funcoes + definicao_lbl_endereco_funcao + $2.c + $5.c +
                 + "'&retorno'" + "@"+ "~"; 
      ts.pop_back(); 
    }
  | ID_EMPILHA_TS CHAVES_FUNCAO CMDs '}'
    {
      string lbl_endereco_funcao = gera_label( "func_" + $1.c[0] );
      string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
      
      $$.c = "{}" + vector<string>{ "'&funcao'" } + lbl_endereco_funcao + "[<=]";
      $$.rmv_from_stack = 0;
      funcoes = funcoes + definicao_lbl_endereco_funcao + $1.c + "&" + $1.c + 
                "arguments" + "@" + "0" + "[@]" + "=" + "^" + $3.c + 
                "'&retorno'" + "@"+ "~";
      in_func--;  
      ts.pop_back(); 
    }
  | '(' E ')'
    { $$.c = $2.c; $$.rmv_from_stack = 0;}
  | '(' OBJECT ')'
    { $$.c = $2.c; $$.rmv_from_stack = 0;}
  | ARRAY
  | '['']' 
    { $$.c = vector<string>{"[]"}; }
  ;

  ID_EMPILHA_TS : ID EMPILHA_TS 
                  { declara_var( Let, $1.c[0], $1.linha, $1.coluna ); in_func++; }

  ANONYM_FUNC : FUNCTION { in_func++; } '(' LISTA_ARGs ')' '{' CMDs '}'
                {
                  string lbl_endereco_funcao = gera_label( "func_" );
                  string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
                  
                  $$.c = "{}" + vector<string>{ "'&funcao'" } + lbl_endereco_funcao + "[<=]";
                  funcoes = funcoes + definicao_lbl_endereco_funcao + $4.c + $7.c +
                            "undefined" + "@" + "'&retorno'" + "@"+ "~";
                  ts.pop_back(); 
                  in_func--;
                }

  OBJECT : '{' OBJECT_PROPs '}'
           { $$.c = "{}" + $2.c; }
          | BLVAZIO
           ;
  
  OBJECT_PROP : ID ':' E
               { $$.c = $1.c + $3.c + "[<=]"; }
              | ID ':' OBJECT
               {$$.c = $1.c + $3.c + "[<=]";}
             ;

  OBJECT_PROPs : OBJECT_PROPs ',' OBJECT_PROP
                 { $$.c = $1.c + $3.c; }
              | OBJECT_PROP
              ;

  ARRAY : '[' ARRAY_ELEMs ']'
          { $$.c = "[]" + $2.c; }
          ;

  ARRAY_ELEM : E
             | OBJECT
             ;

  ARRAY_ELEMs : ARRAY_ELEMs ',' ARRAY_ELEM
               { $$.c = $1.c + to_string( $1.n_args ) + $3.c + "[<=]";
                $$.n_args++; }
              | ARRAY_ELEM
              { $$.c = to_string( $1.n_args ) + $1.c + "[<=]";
                $$.n_args++; }
              ;

%%

#include "lex.yy.c"

vector<string> declara_var( TipoDecl tipo, string nome, int linha, int coluna ) {
       
  auto& topo = ts.back();    
       
  if( topo.count( nome ) == 0 ) {
    topo[nome] = Simbolo{ tipo, linha, coluna };
    return vector<string>{ nome, "&" };
  }
  else if( tipo == Var && topo[nome].tipo == Var ) {
    topo[nome] = Simbolo{ tipo, linha, coluna };
    return vector<string>{};
  } 
  else {
    cerr << "Erro: a variável '" << nome << "' já foi declarada na linha " << topo[nome].linha << "." << endl;
    exit( 1 );     
  }
}

void checa_retorno(int in_func) {
  if ( !in_func ) {
    cerr << "Erro: Não é permitido 'return' fora de funções." << endl;
    exit( 1 ); 
  }
  else return;
}

void checa_simbolo( string nome, bool modificavel ) {
  for( int i = ts.size() - 1; i >= 0; i-- ) {  
    auto& atual = ts[i];
    
    if( atual.count( nome ) > 0 ) {
      if( modificavel && atual[nome].tipo == Const ) {
        cerr << "Variavel '" << nome << "' não pode ser modificada." << endl;
        exit( 1 );     
      }
      else 
        return;
    }
  }

  cerr << "Variavel '" << nome << "' não declarada." << endl;
  exit( 1 );     
}


void yyerror( const char* st ) {
   cerr << st << endl; 
   cerr << "Proximo a: " << yytext << endl;
   exit( 1 );
}

int main( int argc, char* argv[] ) {
  yyparse();
  
  return 0;
}

