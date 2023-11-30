/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "simbs.y"

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
  
  // Só para valor default de argumento        
  vector<string> valor_default; 

  void clear() {
    c.clear();
    valor_default.clear();
    linha = 0;
    coluna = 0;
    n_args = 0;
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
bool in_scope = false;

// Tabela de símbolos - agora é uma pilha
vector< map< string, Simbolo > > ts = { map< string, Simbolo >{} }; 
vector<string> funcoes;

vector<string> declara_var( TipoDecl tipo, string nome, int linha, int coluna );
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


#line 187 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IF = 258,                      /* IF  */
    ELSE = 259,                    /* ELSE  */
    FOR = 260,                     /* FOR  */
    WHILE = 261,                   /* WHILE  */
    LET = 262,                     /* LET  */
    CONST = 263,                   /* CONST  */
    VAR = 264,                     /* VAR  */
    OBJECT = 265,                  /* OBJECT  */
    FUNCTION = 266,                /* FUNCTION  */
    ASM = 267,                     /* ASM  */
    RETURN = 268,                  /* RETURN  */
    ID = 269,                      /* ID  */
    CDOUBLE = 270,                 /* CDOUBLE  */
    CSTRING = 271,                 /* CSTRING  */
    CINT = 272,                    /* CINT  */
    BOOL = 273,                    /* BOOL  */
    AND = 274,                     /* AND  */
    OR = 275,                      /* OR  */
    DIF = 276,                     /* DIF  */
    IGUAL = 277,                   /* IGUAL  */
    MAIS_IGUAL = 278,              /* MAIS_IGUAL  */
    MAIS_MAIS = 279,               /* MAIS_MAIS  */
    SETA = 280,                    /* SETA  */
    PARENTESES_FUNCAO = 281,       /* PARENTESES_FUNCAO  */
    MA_IG = 282,                   /* MA_IG  */
    ME_IG = 283                    /* ME_IG  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define LET 262
#define CONST 263
#define VAR 264
#define OBJECT 265
#define FUNCTION 266
#define ASM 267
#define RETURN 268
#define ID 269
#define CDOUBLE 270
#define CSTRING 271
#define CINT 272
#define BOOL 273
#define AND 274
#define OR 275
#define DIF 276
#define IGUAL 277
#define MAIS_IGUAL 278
#define MAIS_MAIS 279
#define SETA 280
#define PARENTESES_FUNCAO 281
#define MA_IG 282
#define ME_IG 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IF = 3,                         /* IF  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FOR = 5,                        /* FOR  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_LET = 7,                        /* LET  */
  YYSYMBOL_CONST = 8,                      /* CONST  */
  YYSYMBOL_VAR = 9,                        /* VAR  */
  YYSYMBOL_OBJECT = 10,                    /* OBJECT  */
  YYSYMBOL_FUNCTION = 11,                  /* FUNCTION  */
  YYSYMBOL_ASM = 12,                       /* ASM  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_ID = 14,                        /* ID  */
  YYSYMBOL_CDOUBLE = 15,                   /* CDOUBLE  */
  YYSYMBOL_CSTRING = 16,                   /* CSTRING  */
  YYSYMBOL_CINT = 17,                      /* CINT  */
  YYSYMBOL_BOOL = 18,                      /* BOOL  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_DIF = 21,                       /* DIF  */
  YYSYMBOL_IGUAL = 22,                     /* IGUAL  */
  YYSYMBOL_MAIS_IGUAL = 23,                /* MAIS_IGUAL  */
  YYSYMBOL_MAIS_MAIS = 24,                 /* MAIS_MAIS  */
  YYSYMBOL_SETA = 25,                      /* SETA  */
  YYSYMBOL_PARENTESES_FUNCAO = 26,         /* PARENTESES_FUNCAO  */
  YYSYMBOL_27_ = 27,                       /* '='  */
  YYSYMBOL_MA_IG = 28,                     /* MA_IG  */
  YYSYMBOL_ME_IG = 29,                     /* ME_IG  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '['  */
  YYSYMBOL_38_ = 38,                       /* '('  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '.'  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '}'  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_S = 47,                         /* S  */
  YYSYMBOL_CMDs = 48,                      /* CMDs  */
  YYSYMBOL_CMD = 49,                       /* CMD  */
  YYSYMBOL_EMPILHA_TS = 50,                /* EMPILHA_TS  */
  YYSYMBOL_CMD_FUNC = 51,                  /* CMD_FUNC  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_LISTA_ARGs = 53,                /* LISTA_ARGs  */
  YYSYMBOL_ARGs = 54,                      /* ARGs  */
  YYSYMBOL_ARG = 55,                       /* ARG  */
  YYSYMBOL_CMD_FOR = 56,                   /* CMD_FOR  */
  YYSYMBOL_PRIM_E = 57,                    /* PRIM_E  */
  YYSYMBOL_CMD_LET = 58,                   /* CMD_LET  */
  YYSYMBOL_LET_VARs = 59,                  /* LET_VARs  */
  YYSYMBOL_LET_VAR = 60,                   /* LET_VAR  */
  YYSYMBOL_CMD_VAR = 61,                   /* CMD_VAR  */
  YYSYMBOL_VAR_VARs = 62,                  /* VAR_VARs  */
  YYSYMBOL_VAR_VAR = 63,                   /* VAR_VAR  */
  YYSYMBOL_CMD_CONST = 64,                 /* CMD_CONST  */
  YYSYMBOL_CONST_VARs = 65,                /* CONST_VARs  */
  YYSYMBOL_CONST_VAR = 66,                 /* CONST_VAR  */
  YYSYMBOL_CMD_IF = 67,                    /* CMD_IF  */
  YYSYMBOL_LVALUEPROP = 68,                /* LVALUEPROP  */
  YYSYMBOL_LISTA_PARAMs = 69,              /* LISTA_PARAMs  */
  YYSYMBOL_PARAMs = 70,                    /* PARAMs  */
  YYSYMBOL_E = 71                          /* E  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   519

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   283


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    36,     2,     2,
      38,    43,    34,    32,    44,    33,    40,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
      30,    27,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    37,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    42,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   137,   138,   142,   143,   144,   145,   146,
     147,   149,   150,   151,   153,   155,   160,   163,   163,   179,
     180,   183,   203,   225,   231,   240,   256,   257,   258,   259,
     263,   266,   267,   270,   272,   278,   281,   282,   285,   287,
     292,   295,   296,   299,   305,   318,   350,   352,   354,   358,
     359,   362,   365,   370,   372,   374,   376,   378,   380,   382,
     384,   386,   388,   390,   392,   394,   396,   398,   400,   402,
     404,   406,   408,   410,   412,   416,   418,   420,   422,   425,
     427,   429,   431,   433,   435,   437,   439,   441,   443
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IF", "ELSE", "FOR",
  "WHILE", "LET", "CONST", "VAR", "OBJECT", "FUNCTION", "ASM", "RETURN",
  "ID", "CDOUBLE", "CSTRING", "CINT", "BOOL", "AND", "OR", "DIF", "IGUAL",
  "MAIS_IGUAL", "MAIS_MAIS", "SETA", "PARENTESES_FUNCAO", "'='", "MA_IG",
  "ME_IG", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "'('",
  "'{'", "'.'", "';'", "'}'", "')'", "','", "']'", "$accept", "S", "CMDs",
  "CMD", "EMPILHA_TS", "CMD_FUNC", "$@1", "LISTA_ARGs", "ARGs", "ARG",
  "CMD_FOR", "PRIM_E", "CMD_LET", "LET_VARs", "LET_VAR", "CMD_VAR",
  "VAR_VARs", "VAR_VAR", "CMD_CONST", "CONST_VARs", "CONST_VAR", "CMD_IF",
  "LVALUEPROP", "LISTA_PARAMs", "PARAMs", "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -122,    14,   175,  -122,   -23,   -18,    17,    19,    24,  -122,
      25,   226,   -17,  -122,  -122,  -122,  -122,   226,   226,    -4,
     252,     1,  -122,  -122,  -122,  -122,     3,     4,     8,  -122,
     -15,   197,   226,     9,    23,  -122,    13,    26,  -122,    29,
      31,  -122,    33,  -122,     1,   406,   226,   226,   226,  -122,
     448,    34,  -122,    37,    49,    38,   337,  -122,  -122,  -122,
    -122,  -122,   226,   278,    40,   226,   226,   226,  -122,   -26,
     226,   226,   226,   226,   226,   226,   226,   226,   226,    69,
    -122,   360,    43,  -122,  -122,  -122,   448,   226,    17,   226,
      19,   226,    24,    47,  -122,   468,   468,   448,    44,    70,
     226,  -122,    83,   468,    57,    61,   448,  -122,   468,   468,
     468,    59,    63,   479,   479,    34,    34,    -8,    -8,    -8,
     297,    66,   448,    73,   175,   226,   448,  -122,   448,  -122,
     448,  -122,  -122,  -122,   226,   448,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,   226,   102,   427,    97,   448,   317,   175,
     226,    86,    72,    74,  -122,  -122,  -122,   383,   226,    78,
      97,   175,   448,  -122,  -122,  -122,   135,  -122
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     0,    84,
       0,     0,    16,    75,    77,    76,    78,     0,     0,     0,
      50,    16,    14,     3,     9,    11,     0,     0,     0,     8,
      80,     0,     0,     0,    33,    30,    32,     0,    40,    42,
      38,    35,    37,    17,     0,     0,     0,     0,     0,    86,
      79,    73,    85,     0,     0,    49,    52,    83,     4,     5,
       6,     7,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    50,     0,
      13,     0,     0,    26,    27,    28,    29,     0,     0,     0,
       0,     0,     0,     0,    10,    63,    62,    55,    83,     0,
       0,    81,     0,    60,     0,     0,    56,    12,    65,    64,
      59,     0,     0,    66,    67,    68,    69,    70,    71,    72,
       0,     0,    52,    47,     0,     0,    34,    31,    43,    41,
      39,    36,    16,    82,     0,    51,    15,    58,    57,    54,
      53,    46,    74,     0,    45,     0,    20,    79,     0,     0,
       0,    23,     0,    19,    22,    48,    44,     0,     0,     0,
       0,     0,    24,     4,    21,    25,     0,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -122,  -122,   -56,  -121,   -20,  -122,  -122,  -122,  -122,   -41,
    -122,  -122,    93,    39,  -122,    95,    41,  -122,    96,    45,
    -122,  -122,  -122,    52,  -122,   -11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    23,    49,    24,    93,   152,   153,   154,
      25,    82,    26,    35,    36,    27,    41,    42,    28,    38,
      39,    29,    30,    54,    55,    31
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    58,   102,   144,    46,    47,    50,    51,    62,    56,
      48,   111,    63,   112,     3,    32,     6,     7,     8,     9,
      33,    81,    86,    12,    13,    14,    15,    16,   156,    77,
      78,    34,    79,    37,    17,    95,    96,    97,    40,    43,
     165,    52,    18,    57,    59,    60,    19,    20,    44,    61,
      87,   103,   106,    89,   108,   109,   110,    88,    91,   113,
     114,   115,   116,   117,   118,   119,   120,   122,    74,    75,
      76,    77,    78,    90,    79,    99,   126,    92,   128,    98,
     130,   107,   100,   123,   125,   132,     4,   133,     5,   135,
       6,     7,     8,     9,    10,   134,    11,    12,    13,    14,
      15,    16,   137,   138,   139,   140,   149,   166,    17,   142,
     143,   151,   146,   158,   145,   159,    18,   163,   160,   164,
      19,    20,    21,   147,    22,   136,    83,   127,    84,    85,
     121,     0,   148,   131,     0,   129,     0,     0,     4,   157,
       5,     0,     6,     7,     8,     9,    10,   162,    11,    12,
      13,    14,    15,    16,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,    19,    20,    21,     0,    22,   167,     4,     0,
       5,     0,     6,     7,     8,     9,    10,     0,    11,    12,
      13,    14,    15,    16,     0,     0,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     0,     0,     0,    18,    64,
       0,     0,    19,    20,    21,     0,    22,     0,    65,    66,
      67,    68,     0,     0,    69,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     9,    79,    80,     0,
      12,    13,    14,    15,    16,     0,     0,     0,     0,     0,
       0,    17,     0,     0,     0,     0,     0,     0,     0,    18,
       0,     0,     9,    19,    20,    44,    12,    13,    14,    15,
      16,     0,     0,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,     0,    18,     0,     0,     9,    19,
      20,    53,    12,    13,    14,    15,    16,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,     0,   104,    20,   105,    65,    66,
      67,    68,     0,     0,    69,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,    79,    65,    66,
      67,    68,   141,     0,    69,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,    79,    65,    66,
      67,    68,   155,     0,    69,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,    79,     0,     0,
     101,    65,    66,    67,    68,     0,     0,    69,     0,     0,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
      79,     0,     0,   124,    65,    66,    67,    68,     0,     0,
      69,     0,     0,    70,    71,    72,    73,    74,    75,    76,
      77,    78,     0,    79,     0,     0,   161,    65,    66,    67,
      68,     0,     0,    69,     0,     0,    70,    71,    72,    73,
      74,    75,    76,    77,    78,     0,    79,    94,    65,    66,
      67,    68,     0,     0,    69,     0,     0,    70,    71,    72,
      73,    74,    75,    76,    77,    78,     0,    79,   150,    65,
      66,    67,    68,     0,     0,    69,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,    79,    -1,
      -1,    -1,    -1,     0,     0,     0,     0,     0,    70,    71,
      72,    73,    74,    75,    76,    77,    78,     0,    79,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,     0,    79
};

static const yytype_int16 yycheck[] =
{
      11,    21,    58,   124,    21,    22,    17,    18,    23,    20,
      27,    37,    27,    39,     0,    38,     7,     8,     9,    10,
      38,    32,    33,    14,    15,    16,    17,    18,   149,    37,
      38,    14,    40,    14,    25,    46,    47,    48,    14,    14,
     161,    45,    33,    42,    41,    41,    37,    38,    39,    41,
      27,    62,    63,    27,    65,    66,    67,    44,    27,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    34,    35,
      36,    37,    38,    44,    40,    26,    87,    44,    89,    42,
      91,    41,    44,    14,    41,    38,     3,    43,     5,   100,
       7,     8,     9,    10,    11,    25,    13,    14,    15,    16,
      17,    18,    45,    42,    45,    42,     4,   163,    25,    43,
      37,    14,   132,    27,   125,    43,    33,    39,    44,   160,
      37,    38,    39,   134,    41,    42,    33,    88,    33,    33,
      78,    -1,   143,    92,    -1,    90,    -1,    -1,     3,   150,
       5,    -1,     7,     8,     9,    10,    11,   158,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,
      -1,    -1,    37,    38,    39,    -1,    41,    42,     3,    -1,
       5,    -1,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    12,
      -1,    -1,    37,    38,    39,    -1,    41,    -1,    21,    22,
      23,    24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    10,    40,    41,    -1,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    -1,    10,    37,    38,    39,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    10,    37,
      38,    39,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    37,    38,    39,    21,    22,
      23,    24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    21,    22,
      23,    24,    45,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    21,    22,
      23,    24,    45,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    -1,    -1,
      43,    21,    22,    23,    24,    -1,    -1,    27,    -1,    -1,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      40,    -1,    -1,    43,    21,    22,    23,    24,    -1,    -1,
      27,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    40,    -1,    -1,    43,    21,    22,    23,
      24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    40,    41,    21,    22,
      23,    24,    -1,    -1,    27,    -1,    -1,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    40,    41,    21,
      22,    23,    24,    -1,    -1,    27,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    40,    21,
      22,    23,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    40,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    40
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    47,    48,     0,     3,     5,     7,     8,     9,    10,
      11,    13,    14,    15,    16,    17,    18,    25,    33,    37,
      38,    39,    41,    49,    51,    56,    58,    61,    64,    67,
      68,    71,    38,    38,    14,    59,    60,    14,    65,    66,
      14,    62,    63,    14,    39,    71,    21,    22,    27,    50,
      71,    71,    45,    39,    69,    70,    71,    42,    50,    41,
      41,    41,    23,    27,    12,    21,    22,    23,    24,    27,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    40,
      41,    71,    57,    58,    61,    64,    71,    27,    44,    27,
      44,    27,    44,    52,    41,    71,    71,    71,    42,    26,
      44,    43,    48,    71,    37,    39,    71,    41,    71,    71,
      71,    37,    39,    71,    71,    71,    71,    71,    71,    71,
      71,    69,    71,    14,    43,    41,    71,    59,    71,    65,
      71,    62,    38,    43,    25,    71,    42,    45,    42,    45,
      42,    45,    43,    37,    49,    71,    50,    71,    71,     4,
      41,    14,    53,    54,    55,    45,    49,    71,    27,    43,
      44,    43,    71,    39,    55,    49,    48,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    48,    48,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    50,    52,    51,    53,
      53,    54,    54,    55,    55,    56,    57,    57,    57,    57,
      58,    59,    59,    60,    60,    61,    62,    62,    63,    63,
      64,    65,    65,    66,    67,    67,    68,    68,    68,    69,
      69,    70,    70,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     1,     1,
       3,     1,     3,     2,     1,     4,     0,     0,    10,     1,
       0,     3,     1,     1,     3,     9,     1,     1,     1,     1,
       2,     3,     1,     1,     3,     2,     3,     1,     1,     3,
       2,     3,     1,     3,     7,     5,     4,     3,     6,     1,
       0,     3,     1,     4,     4,     3,     3,     4,     4,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     4,     1,     1,     1,     1,     1,
       1,     3,     4,     2,     1,     2,     2,     2,     5
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: CMDs  */
#line 134 "simbs.y"
         { print( resolve_enderecos( yyvsp[0].c + "." + funcoes ) ); }
#line 1513 "y.tab.c"
    break;

  case 3: /* CMDs: CMDs CMD  */
#line 137 "simbs.y"
                 { yyval.c = yyvsp[-1].c + yyvsp[0].c; }
#line 1519 "y.tab.c"
    break;

  case 4: /* CMDs: %empty  */
#line 138 "simbs.y"
                 { yyval.clear(); }
#line 1525 "y.tab.c"
    break;

  case 10: /* CMD: RETURN E ';'  */
#line 148 "simbs.y"
      { yyval.c = yyvsp[-1].c + "'&retorno'" + "@" + "~"; }
#line 1531 "y.tab.c"
    break;

  case 12: /* CMD: E ASM ';'  */
#line 150 "simbs.y"
                        { yyval.c = yyvsp[-2].c + yyvsp[-1].c + "^"; }
#line 1537 "y.tab.c"
    break;

  case 13: /* CMD: E ';'  */
#line 152 "simbs.y"
      { yyval.c = yyvsp[-1].c + "^"; }
#line 1543 "y.tab.c"
    break;

  case 14: /* CMD: ';'  */
#line 154 "simbs.y"
      { yyval.clear(); }
#line 1549 "y.tab.c"
    break;

  case 15: /* CMD: '{' EMPILHA_TS CMDs '}'  */
#line 156 "simbs.y"
      { ts.pop_back();
        yyval.c = vector<string>{"<{"} + yyvsp[-1].c + vector<string>{"}>"};  }
#line 1556 "y.tab.c"
    break;

  case 16: /* EMPILHA_TS: %empty  */
#line 160 "simbs.y"
             { ts.push_back( map< string, Simbolo >{} ); }
#line 1562 "y.tab.c"
    break;

  case 17: /* $@1: %empty  */
#line 163 "simbs.y"
                       { declara_var( Var, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1568 "y.tab.c"
    break;

  case 18: /* CMD_FUNC: FUNCTION ID $@1 '(' EMPILHA_TS LISTA_ARGs ')' '{' CMDs '}'  */
#line 165 "simbs.y"
           { 
             string lbl_endereco_funcao = gera_label( "func_" + yyvsp[-8].c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             yyval.c = yyvsp[-8].c + "&" + yyvsp[-8].c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + yyvsp[-4].c + yyvsp[-1].c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back(); 
             in_scope = false;
           }
#line 1584 "y.tab.c"
    break;

  case 20: /* LISTA_ARGs: %empty  */
#line 180 "simbs.y"
             { yyval.clear(); }
#line 1590 "y.tab.c"
    break;

  case 21: /* ARGs: ARGs ',' ARG  */
#line 184 "simbs.y"
       { // a & a arguments @ 0 [@] = ^ 
         yyval.c = yyvsp[-2].c + yyvsp[0].c + "&" + yyvsp[0].c + "arguments" + "@" + to_string( yyvsp[-2].n_args )
                + "[@]" + "=" + "^"; 
        in_scope = true; 
         if( yyvsp[0].valor_default.size() > 0 ) {
           string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
           yyval.c = yyval.c + declara_var( Var, "placeholder", 1, 1 ) + 
                 yyvsp[0].c + "@" + "placeholder" + "@" + "!=" +
                 lbl_true + "?" + yyvsp[0].c + yyvsp[0].valor_default + "=" + "^" +
                 lbl_fim_if + "#" +
                 definicao_lbl_true + 
                 definicao_lbl_fim_if
                 ;
         }
         yyval.n_args = yyvsp[-2].n_args + yyvsp[0].n_args; 
       }
#line 1614 "y.tab.c"
    break;

  case 22: /* ARGs: ARG  */
#line 204 "simbs.y"
       { // a & a arguments @ 0 [@] = ^ 
         yyval.c = yyvsp[0].c + "&" + yyvsp[0].c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
                
         in_scope = true; 
         if( yyvsp[0].valor_default.size() > 0 ) {
           string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
           yyval.c = yyval.c + declara_var( Var, "placeholder", 1, 1 ) + 
                 yyvsp[0].c + "@" + "placeholder" + "@" + "!=" +
                 lbl_true + "?" + yyvsp[0].c + yyvsp[0].valor_default + "=" + "^" +
                 lbl_fim_if + "#" +
                 definicao_lbl_true + 
                 definicao_lbl_fim_if
                 ;
         }
         yyval.n_args = yyvsp[0].n_args; 
       }
#line 1638 "y.tab.c"
    break;

  case 23: /* ARG: ID  */
#line 226 "simbs.y"
      { yyval.c = yyvsp[0].c;      
        yyval.n_args = 1;
        yyval.valor_default.clear();
        declara_var( Let, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); 
      }
#line 1648 "y.tab.c"
    break;

  case 24: /* ARG: ID '=' E  */
#line 232 "simbs.y"
      { // Código do IF
        yyval.c = yyvsp[-2].c;
        yyval.n_args = 1;
        yyval.valor_default = yyvsp[0].c;         
        declara_var( Let, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ); 
      }
#line 1659 "y.tab.c"
    break;

  case 25: /* CMD_FOR: FOR '(' PRIM_E ';' E ';' E ')' CMD  */
#line 241 "simbs.y"
        { string lbl_fim_for = gera_label( "fim_for" );
          string lbl_condicao_for = gera_label( "condicao_for" );
          string lbl_comando_for = gera_label( "comando_for" );
          string definicao_lbl_fim_for = ":" + lbl_fim_for;
          string definicao_lbl_condicao_for = ":" + lbl_condicao_for;
          string definicao_lbl_comando_for = ":" + lbl_comando_for;
          
          yyval.c = yyvsp[-6].c + definicao_lbl_condicao_for +
                 yyvsp[-4].c + lbl_comando_for + "?" + lbl_fim_for + "#" +
                 definicao_lbl_comando_for + yyvsp[0].c + 
                 yyvsp[-2].c + "^" + lbl_condicao_for + "#" +
                 definicao_lbl_fim_for;
        }
#line 1677 "y.tab.c"
    break;

  case 29: /* PRIM_E: E  */
#line 260 "simbs.y"
         { yyval.c = yyvsp[0].c + "^"; }
#line 1683 "y.tab.c"
    break;

  case 30: /* CMD_LET: LET LET_VARs  */
#line 263 "simbs.y"
                       { yyval.c = yyvsp[0].c; }
#line 1689 "y.tab.c"
    break;

  case 31: /* LET_VARs: LET_VAR ',' LET_VARs  */
#line 266 "simbs.y"
                                { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1695 "y.tab.c"
    break;

  case 33: /* LET_VAR: ID  */
#line 271 "simbs.y"
          { yyval.c = declara_var( Let, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1701 "y.tab.c"
    break;

  case 34: /* LET_VAR: ID '=' E  */
#line 273 "simbs.y"
          { 
            yyval.c = declara_var( Let, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                   yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1709 "y.tab.c"
    break;

  case 35: /* CMD_VAR: VAR VAR_VARs  */
#line 278 "simbs.y"
                       { yyval.c = yyvsp[0].c; }
#line 1715 "y.tab.c"
    break;

  case 36: /* VAR_VARs: VAR_VAR ',' VAR_VARs  */
#line 281 "simbs.y"
                                { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1721 "y.tab.c"
    break;

  case 38: /* VAR_VAR: ID  */
#line 286 "simbs.y"
          { yyval.c = declara_var( Var, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1727 "y.tab.c"
    break;

  case 39: /* VAR_VAR: ID '=' E  */
#line 288 "simbs.y"
          {  yyval.c = declara_var( Var, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                    yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1734 "y.tab.c"
    break;

  case 40: /* CMD_CONST: CONST CONST_VARs  */
#line 292 "simbs.y"
                            { yyval.c = yyvsp[0].c; }
#line 1740 "y.tab.c"
    break;

  case 41: /* CONST_VARs: CONST_VAR ',' CONST_VARs  */
#line 295 "simbs.y"
                                      { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1746 "y.tab.c"
    break;

  case 43: /* CONST_VAR: ID '=' E  */
#line 300 "simbs.y"
            { yyval.c = declara_var( Const, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                     yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1753 "y.tab.c"
    break;

  case 44: /* CMD_IF: IF '(' E ')' CMD ELSE CMD  */
#line 306 "simbs.y"
         { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            yyval.c = yyvsp[-4].c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   yyvsp[0].c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + yyvsp[-2].c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         }
#line 1770 "y.tab.c"
    break;

  case 45: /* CMD_IF: IF '(' E ')' CMD  */
#line 319 "simbs.y"
        {  string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            yyval.c = yyvsp[-2].c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   lbl_fim_if + "#" +           // Código do False
                   definicao_lbl_true + yyvsp[0].c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;}
#line 1786 "y.tab.c"
    break;

  case 46: /* LVALUEPROP: E '[' E ']'  */
#line 351 "simbs.y"
              { yyval.c = yyvsp[-3].c+ yyvsp[-1].c; }
#line 1792 "y.tab.c"
    break;

  case 47: /* LVALUEPROP: E '.' ID  */
#line 353 "simbs.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1798 "y.tab.c"
    break;

  case 48: /* LVALUEPROP: E '.' ID '[' E ']'  */
#line 355 "simbs.y"
              { yyval.c = yyvsp[-5].c + yyvsp[-3].c + "[@]" + yyvsp[-1].c; }
#line 1804 "y.tab.c"
    break;

  case 50: /* LISTA_PARAMs: %empty  */
#line 359 "simbs.y"
             { yyval.clear(); }
#line 1810 "y.tab.c"
    break;

  case 51: /* PARAMs: PARAMs ',' E  */
#line 363 "simbs.y"
       { yyval.c = yyvsp[-2].c + yyvsp[0].c;
         yyval.n_args = yyvsp[-2].n_args + 1; }
#line 1817 "y.tab.c"
    break;

  case 52: /* PARAMs: E  */
#line 366 "simbs.y"
       { yyval.c = yyvsp[0].c;
         yyval.n_args = yyvsp[0].n_args + 1; }
#line 1824 "y.tab.c"
    break;

  case 53: /* E: E '=' '{' '}'  */
#line 371 "simbs.y"
    { checa_simbolo( yyvsp[-3].c[0], true ); yyval.c = yyvsp[-3].c + "{}" + "="; }
#line 1830 "y.tab.c"
    break;

  case 54: /* E: E '=' '[' ']'  */
#line 373 "simbs.y"
    { checa_simbolo( yyvsp[-3].c[0], true ); yyval.c = yyvsp[-3].c + "[]" + "="; }
#line 1836 "y.tab.c"
    break;

  case 55: /* E: ID '=' E  */
#line 375 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[0].c + "="; }
#line 1842 "y.tab.c"
    break;

  case 56: /* E: LVALUEPROP '=' E  */
#line 377 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[0].c + "[=]"; }
#line 1848 "y.tab.c"
    break;

  case 57: /* E: LVALUEPROP '=' '{' '}'  */
#line 379 "simbs.y"
  { checa_simbolo( yyvsp[-3].c[0], true ); yyval.c = yyvsp[-3].c + vector<string>{"[]"} + "[=]"; }
#line 1854 "y.tab.c"
    break;

  case 58: /* E: LVALUEPROP '=' '[' ']'  */
#line 381 "simbs.y"
    { checa_simbolo( yyvsp[-3].c[0], true ); yyval.c = yyvsp[-3].c + vector<string>{"[]"} + "[=]"; }
#line 1860 "y.tab.c"
    break;

  case 59: /* E: E MAIS_IGUAL E  */
#line 383 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[-2].c + "@" + yyvsp[0].c + "+" + "="; }
#line 1866 "y.tab.c"
    break;

  case 60: /* E: LVALUEPROP MAIS_IGUAL E  */
#line 385 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[-2].c + "[@]" + yyvsp[0].c + "+" + "[=]"; }
#line 1872 "y.tab.c"
    break;

  case 61: /* E: E MAIS_MAIS  */
#line 387 "simbs.y"
    { checa_simbolo( yyvsp[-1].c[0], true ); yyval.c = yyvsp[-1].c + "@" + yyvsp[-1].c + yyvsp[-1].c + "@" + "1" + "+" + "=" + "^"; }
#line 1878 "y.tab.c"
    break;

  case 62: /* E: ID IGUAL E  */
#line 389 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + "@" + yyvsp[0].c + "==";}
#line 1884 "y.tab.c"
    break;

  case 63: /* E: ID DIF E  */
#line 391 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "!="; }
#line 1890 "y.tab.c"
    break;

  case 64: /* E: E IGUAL E  */
#line 393 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "=="; }
#line 1896 "y.tab.c"
    break;

  case 65: /* E: E DIF E  */
#line 395 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "!="; }
#line 1902 "y.tab.c"
    break;

  case 66: /* E: E '<' E  */
#line 397 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1908 "y.tab.c"
    break;

  case 67: /* E: E '>' E  */
#line 399 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1914 "y.tab.c"
    break;

  case 68: /* E: E '+' E  */
#line 401 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1920 "y.tab.c"
    break;

  case 69: /* E: E '-' E  */
#line 403 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1926 "y.tab.c"
    break;

  case 70: /* E: E '*' E  */
#line 405 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1932 "y.tab.c"
    break;

  case 71: /* E: E '/' E  */
#line 407 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1938 "y.tab.c"
    break;

  case 72: /* E: E '%' E  */
#line 409 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1944 "y.tab.c"
    break;

  case 73: /* E: '-' E  */
#line 411 "simbs.y"
    { yyval.c = "0" + yyvsp[0].c + yyvsp[-1].c; }
#line 1950 "y.tab.c"
    break;

  case 74: /* E: E '(' LISTA_PARAMs ')'  */
#line 413 "simbs.y"
    {
      yyval.c = yyvsp[-1].c + to_string( yyvsp[-1].n_args ) + yyvsp[-3].c + "$";
    }
#line 1958 "y.tab.c"
    break;

  case 75: /* E: CDOUBLE  */
#line 417 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1964 "y.tab.c"
    break;

  case 76: /* E: CINT  */
#line 419 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1970 "y.tab.c"
    break;

  case 77: /* E: CSTRING  */
#line 421 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1976 "y.tab.c"
    break;

  case 78: /* E: BOOL  */
#line 423 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1982 "y.tab.c"
    break;

  case 79: /* E: E  */
#line 426 "simbs.y"
    { if(!in_scope) checa_simbolo( yyvsp[0].c[0], false ); yyval.c = yyvsp[0].c + "@"; }
#line 1988 "y.tab.c"
    break;

  case 80: /* E: LVALUEPROP  */
#line 428 "simbs.y"
    { if(!in_scope) checa_simbolo( yyvsp[0].c[0], false ); yyval.c = yyvsp[0].c + "[@]"; }
#line 1994 "y.tab.c"
    break;

  case 81: /* E: '(' E ')'  */
#line 430 "simbs.y"
    { yyval.c = yyvsp[-1].c; }
#line 2000 "y.tab.c"
    break;

  case 82: /* E: '(' '{' '}' ')'  */
#line 432 "simbs.y"
    { yyval.c = vector<string>{"{}"}; }
#line 2006 "y.tab.c"
    break;

  case 83: /* E: '{' '}'  */
#line 434 "simbs.y"
    { yyval.c = vector<string>{"{}"}; }
#line 2012 "y.tab.c"
    break;

  case 84: /* E: OBJECT  */
#line 436 "simbs.y"
    {yyval.c = vector<string>{"{}"};}
#line 2018 "y.tab.c"
    break;

  case 85: /* E: '[' ']'  */
#line 438 "simbs.y"
    { yyval.c = vector<string>{"[]"}; }
#line 2024 "y.tab.c"
    break;

  case 86: /* E: ID EMPILHA_TS  */
#line 440 "simbs.y"
    { declara_var( Let, yyvsp[-1].c[0], yyvsp[-1].linha, yyvsp[-1].coluna ); }
#line 2030 "y.tab.c"
    break;

  case 87: /* E: SETA E  */
#line 442 "simbs.y"
    { ts.pop_back(); }
#line 2036 "y.tab.c"
    break;

  case 88: /* E: '(' LISTA_PARAMs PARENTESES_FUNCAO SETA E  */
#line 444 "simbs.y"
    { ts.pop_back(); }
#line 2042 "y.tab.c"
    break;


#line 2046 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 448 "simbs.y"


#include "lex.yy.c"

vector<string> declara_var( TipoDecl tipo, string nome, int linha, int coluna ) {
//  cerr << "insere_simbolo( " << tipo << ", " << nome 
//       << ", " << linha << ", " << coluna << ")" << endl;
       
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

