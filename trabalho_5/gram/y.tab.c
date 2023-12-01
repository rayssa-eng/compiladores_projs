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
    FUNCTION = 265,                /* FUNCTION  */
    ASM = 266,                     /* ASM  */
    RETURN = 267,                  /* RETURN  */
    ID = 268,                      /* ID  */
    CDOUBLE = 269,                 /* CDOUBLE  */
    CSTRING = 270,                 /* CSTRING  */
    CINT = 271,                    /* CINT  */
    BOOL = 272,                    /* BOOL  */
    BLVAZIO = 273,                 /* BLVAZIO  */
    AND = 274,                     /* AND  */
    OR = 275,                      /* OR  */
    DIF = 276,                     /* DIF  */
    IGUAL = 277,                   /* IGUAL  */
    MAIS_IGUAL = 278,              /* MAIS_IGUAL  */
    MAIS_MAIS = 279,               /* MAIS_MAIS  */
    MA_IG = 280,                   /* MA_IG  */
    ME_IG = 281                    /* ME_IG  */
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
#define FUNCTION 265
#define ASM 266
#define RETURN 267
#define ID 268
#define CDOUBLE 269
#define CSTRING 270
#define CINT 271
#define BOOL 272
#define BLVAZIO 273
#define AND 274
#define OR 275
#define DIF 276
#define IGUAL 277
#define MAIS_IGUAL 278
#define MAIS_MAIS 279
#define MA_IG 280
#define ME_IG 281

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
  YYSYMBOL_FUNCTION = 10,                  /* FUNCTION  */
  YYSYMBOL_ASM = 11,                       /* ASM  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_ID = 13,                        /* ID  */
  YYSYMBOL_CDOUBLE = 14,                   /* CDOUBLE  */
  YYSYMBOL_CSTRING = 15,                   /* CSTRING  */
  YYSYMBOL_CINT = 16,                      /* CINT  */
  YYSYMBOL_BOOL = 17,                      /* BOOL  */
  YYSYMBOL_BLVAZIO = 18,                   /* BLVAZIO  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_DIF = 21,                       /* DIF  */
  YYSYMBOL_IGUAL = 22,                     /* IGUAL  */
  YYSYMBOL_MAIS_IGUAL = 23,                /* MAIS_IGUAL  */
  YYSYMBOL_MAIS_MAIS = 24,                 /* MAIS_MAIS  */
  YYSYMBOL_25_ = 25,                       /* '='  */
  YYSYMBOL_MA_IG = 26,                     /* MA_IG  */
  YYSYMBOL_ME_IG = 27,                     /* ME_IG  */
  YYSYMBOL_28_ = 28,                       /* '<'  */
  YYSYMBOL_29_ = 29,                       /* '>'  */
  YYSYMBOL_30_ = 30,                       /* '+'  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '*'  */
  YYSYMBOL_33_ = 33,                       /* '/'  */
  YYSYMBOL_34_ = 34,                       /* '%'  */
  YYSYMBOL_35_ = 35,                       /* '['  */
  YYSYMBOL_36_ = 36,                       /* '('  */
  YYSYMBOL_37_ = 37,                       /* '{'  */
  YYSYMBOL_38_ = 38,                       /* '.'  */
  YYSYMBOL_39_ = 39,                       /* ';'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* ')'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_43_ = 43,                       /* ']'  */
  YYSYMBOL_44_ = 44,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_S = 46,                         /* S  */
  YYSYMBOL_CMDs = 47,                      /* CMDs  */
  YYSYMBOL_CMD = 48,                       /* CMD  */
  YYSYMBOL_EMPILHA_TS = 49,                /* EMPILHA_TS  */
  YYSYMBOL_CMD_FUNC = 50,                  /* CMD_FUNC  */
  YYSYMBOL_51_1 = 51,                      /* $@1  */
  YYSYMBOL_LISTA_ARGs = 52,                /* LISTA_ARGs  */
  YYSYMBOL_ARGs = 53,                      /* ARGs  */
  YYSYMBOL_ARG = 54,                       /* ARG  */
  YYSYMBOL_CMD_FOR = 55,                   /* CMD_FOR  */
  YYSYMBOL_PRIM_E = 56,                    /* PRIM_E  */
  YYSYMBOL_CMD_LET = 57,                   /* CMD_LET  */
  YYSYMBOL_LET_VARs = 58,                  /* LET_VARs  */
  YYSYMBOL_LET_VAR = 59,                   /* LET_VAR  */
  YYSYMBOL_CMD_VAR = 60,                   /* CMD_VAR  */
  YYSYMBOL_VAR_VARs = 61,                  /* VAR_VARs  */
  YYSYMBOL_VAR_VAR = 62,                   /* VAR_VAR  */
  YYSYMBOL_CMD_CONST = 63,                 /* CMD_CONST  */
  YYSYMBOL_CONST_VARs = 64,                /* CONST_VARs  */
  YYSYMBOL_CONST_VAR = 65,                 /* CONST_VAR  */
  YYSYMBOL_CMD_IF = 66,                    /* CMD_IF  */
  YYSYMBOL_LVALUE = 67,                    /* LVALUE  */
  YYSYMBOL_LVALUEPROP = 68,                /* LVALUEPROP  */
  YYSYMBOL_LISTA_PARAMs = 69,              /* LISTA_PARAMs  */
  YYSYMBOL_PARAMs = 70,                    /* PARAMs  */
  YYSYMBOL_E = 71,                         /* E  */
  YYSYMBOL_OBJECT = 72,                    /* OBJECT  */
  YYSYMBOL_OBJECT_PROP = 73,               /* OBJECT_PROP  */
  YYSYMBOL_OBJECT_PROPs = 74,              /* OBJECT_PROPs  */
  YYSYMBOL_ARRAY = 75,                     /* ARRAY  */
  YYSYMBOL_ARRAY_ELEM = 76,                /* ARRAY_ELEM  */
  YYSYMBOL_ARRAY_ELEMs = 77                /* ARRAY_ELEMs  */
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
#define YYLAST   438

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   281


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
       2,     2,     2,     2,     2,     2,     2,    34,     2,     2,
      36,    41,    32,    30,    42,    31,    38,    33,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    44,    39,
      28,    25,    29,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    35,     2,    43,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,    40,     2,     2,     2,     2,
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
      26,    27
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   137,   138,   142,   143,   144,   145,   146,
     147,   151,   152,   153,   155,   157,   160,   166,   169,   169,
     185,   186,   189,   209,   231,   237,   246,   262,   263,   264,
     265,   269,   272,   273,   276,   278,   282,   288,   291,   292,
     295,   297,   302,   305,   306,   309,   315,   328,   360,   363,
     365,   367,   371,   372,   375,   378,   383,   387,   389,   395,
     397,   399,   401,   403,   405,   407,   409,   411,   413,   415,
     417,   419,   421,   423,   425,   429,   431,   433,   435,   438,
     440,   442,   444,   446,   453,   457,   459,   463,   465,   468,
     472,   475,   478
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
  "WHILE", "LET", "CONST", "VAR", "FUNCTION", "ASM", "RETURN", "ID",
  "CDOUBLE", "CSTRING", "CINT", "BOOL", "BLVAZIO", "AND", "OR", "DIF",
  "IGUAL", "MAIS_IGUAL", "MAIS_MAIS", "'='", "MA_IG", "ME_IG", "'<'",
  "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "'('", "'{'", "'.'",
  "';'", "'}'", "')'", "','", "']'", "':'", "$accept", "S", "CMDs", "CMD",
  "EMPILHA_TS", "CMD_FUNC", "$@1", "LISTA_ARGs", "ARGs", "ARG", "CMD_FOR",
  "PRIM_E", "CMD_LET", "LET_VARs", "LET_VAR", "CMD_VAR", "VAR_VARs",
  "VAR_VAR", "CMD_CONST", "CONST_VARs", "CONST_VAR", "CMD_IF", "LVALUE",
  "LVALUEPROP", "LISTA_PARAMs", "PARAMs", "E", "OBJECT", "OBJECT_PROP",
  "OBJECT_PROPs", "ARRAY", "ARRAY_ELEM", "ARRAY_ELEMs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-119)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -119,    15,    80,  -119,   -11,    -5,    23,    27,    32,    33,
     243,  -119,  -119,  -119,  -119,  -119,  -119,   243,   243,    89,
    -119,  -119,  -119,  -119,  -119,    36,    38,    40,  -119,   164,
      12,   216,  -119,   243,    -3,    29,  -119,    31,    46,  -119,
      39,    59,  -119,    44,  -119,   344,    34,   382,  -119,   -21,
      78,   290,    58,  -119,  -119,  -119,  -119,   243,   243,   243,
    -119,   243,   243,   243,    61,   243,   243,   243,   243,   243,
     243,   243,   243,   243,   243,     3,    88,  -119,   308,    68,
    -119,  -119,  -119,   382,    89,    23,   243,    27,   243,    32,
      72,  -119,   243,  -119,    65,  -119,     1,  -119,  -119,   128,
     400,   400,   400,   382,   400,   382,  -119,   400,   400,   120,
     120,    34,    34,    -9,    -9,    -9,   254,    73,    71,   382,
      83,   204,   243,   382,  -119,  -119,   382,  -119,   382,  -119,
    -119,  -119,    89,  -119,    78,  -119,  -119,  -119,   243,   243,
     117,   363,   110,   382,  -119,  -119,   382,   272,   204,   243,
     102,    91,    92,  -119,  -119,  -119,   326,   243,    93,   110,
     204,   382,  -119,  -119,  -119,   166,  -119
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,    56,     1,     0,     0,     0,     0,     0,     0,
      56,    48,    75,    77,    76,    78,    16,    56,    56,    56,
      17,    14,     3,     9,    11,     0,     0,     0,     8,    79,
      80,     0,    83,    56,    56,    34,    31,    33,     0,    42,
      44,    40,    37,    39,    18,     0,    73,    90,    92,     0,
       0,     0,     0,     4,     5,     6,     7,    56,    56,    56,
      61,    56,    56,    56,     0,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,     0,    13,     0,     0,
      27,    28,    29,    30,    56,     0,    56,     0,    56,     0,
       0,    10,    56,    89,     0,    88,     0,    81,    82,    56,
      63,    62,    59,    57,    60,    58,    12,    65,    64,    66,
      67,    68,    69,    70,    71,    72,     0,     0,    52,    55,
      50,    56,    56,    35,    36,    32,    45,    43,    41,    38,
      17,    91,    56,    84,     0,    15,    49,    74,    56,    56,
      47,     0,    21,    85,    86,    87,    54,     0,    56,    56,
      24,     0,    20,    23,    51,    46,     0,    56,     0,     0,
      56,    25,     4,    22,    26,    56,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -119,  -119,   -52,  -118,    30,  -119,  -119,  -119,  -119,    -2,
    -119,  -119,   127,    77,  -119,   132,    81,  -119,   138,    90,
    -119,  -119,  -119,  -119,  -119,  -119,   -10,   -82,    56,  -119,
    -119,    99,  -119
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    22,    53,    23,    90,   151,   152,   153,
      24,    79,    25,    36,    37,    26,    42,    43,    27,    39,
      40,    28,    29,    30,   117,   118,    31,    52,    95,    96,
      32,    48,    49
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      45,    99,   124,   140,     6,     7,     8,    46,    47,    51,
      11,    12,    13,    14,    15,     3,    11,    12,    13,    14,
      15,    92,    93,    78,    83,    33,    74,    75,    17,    76,
     155,    34,    18,    19,    17,    62,    35,    63,    18,    19,
      38,   133,   164,   134,   -53,    41,    44,   100,   101,   102,
     144,   103,   104,   105,    84,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   119,    71,    72,    73,    74,
      75,    86,    76,    85,   123,    54,   126,    55,   128,    56,
      -2,    87,    47,     4,    88,     5,    89,     6,     7,     8,
       9,    94,    10,    11,    12,    13,    14,    15,    16,    98,
     106,   120,    11,    12,    13,    14,    15,   122,   130,   132,
     165,    17,   141,   138,   137,    18,    19,    20,   139,    21,
      17,   148,   143,   150,    18,    19,    50,   157,   146,   147,
     162,     4,   158,     5,   159,     6,     7,     8,     9,   156,
      10,    11,    12,    13,    14,    15,    16,   161,   -54,   -54,
      69,    70,    71,    72,    73,    74,    75,   163,    76,    17,
     142,    80,   125,    18,    19,    20,    81,    21,   135,     4,
     129,     5,    82,     6,     7,     8,     9,   127,    10,    11,
      12,    13,    14,    15,    16,    57,    58,    59,    60,    61,
     145,   131,     0,     0,     0,     0,     0,    17,     0,     0,
       0,    18,    19,    20,     0,    21,   166,     4,     0,     5,
       0,     6,     7,     8,     9,     0,    10,    11,    12,    13,
      14,    15,    16,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,    17,     0,    65,    66,    18,
      19,    20,     0,    21,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,    76,    77,    11,    12,    13,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    65,    66,     0,    18,    19,
       0,     0,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     0,    76,    65,    66,     0,     0,   136,     0,     0,
      67,    68,    69,    70,    71,    72,    73,    74,    75,     0,
      76,    65,    66,     0,     0,   154,     0,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     0,    76,    65,
      66,    97,     0,     0,     0,     0,    67,    68,    69,    70,
      71,    72,    73,    74,    75,     0,    76,    65,    66,   121,
       0,     0,     0,     0,    67,    68,    69,    70,    71,    72,
      73,    74,    75,     0,    76,    65,    66,   160,     0,     0,
       0,     0,    67,    68,    69,    70,    71,    72,    73,    74,
      75,     0,    76,    91,    65,    66,     0,     0,     0,     0,
       0,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       0,    76,   149,    65,    66,     0,     0,     0,     0,     0,
      67,    68,    69,    70,    71,    72,    73,    74,    75,     0,
      76,   -54,   -54,     0,     0,     0,     0,     0,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     0,    76
};

static const yytype_int16 yycheck[] =
{
      10,    53,    84,   121,     7,     8,     9,    17,    18,    19,
      13,    14,    15,    16,    17,     0,    13,    14,    15,    16,
      17,    42,    43,    33,    34,    36,    35,    36,    31,    38,
     148,    36,    35,    36,    31,    23,    13,    25,    35,    36,
      13,    40,   160,    42,    41,    13,    13,    57,    58,    59,
     132,    61,    62,    63,    25,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    32,    33,    34,    35,
      36,    25,    38,    42,    84,    39,    86,    39,    88,    39,
       0,    42,    92,     3,    25,     5,    42,     7,     8,     9,
      10,    13,    12,    13,    14,    15,    16,    17,    18,    41,
      39,    13,    13,    14,    15,    16,    17,    39,    36,    44,
     162,    31,   122,    42,    41,    35,    36,    37,    35,    39,
      31,     4,   132,    13,    35,    36,    37,    25,   138,   139,
      37,     3,    41,     5,    42,     7,     8,     9,    10,   149,
      12,    13,    14,    15,    16,    17,    18,   157,    28,    29,
      30,    31,    32,    33,    34,    35,    36,   159,    38,    31,
     130,    34,    85,    35,    36,    37,    34,    39,    40,     3,
      89,     5,    34,     7,     8,     9,    10,    87,    12,    13,
      14,    15,    16,    17,    18,    21,    22,    23,    24,    25,
     134,    92,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    36,    37,    -1,    39,    40,     3,    -1,     5,
      -1,     7,     8,     9,    10,    -1,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    21,    22,    35,
      36,    37,    -1,    39,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    39,    13,    14,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    21,    22,    -1,    35,    36,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    21,    22,    -1,    -1,    43,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    21,    22,    -1,    -1,    43,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38,    21,
      22,    41,    -1,    -1,    -1,    -1,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    -1,    38,    21,    22,    41,
      -1,    -1,    -1,    -1,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    38,    21,    22,    41,    -1,    -1,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    -1,    38,    39,    21,    22,    -1,    -1,    -1,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    21,    22,    -1,    -1,    -1,    -1,    -1,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    21,    22,    -1,    -1,    -1,    -1,    -1,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    46,    47,     0,     3,     5,     7,     8,     9,    10,
      12,    13,    14,    15,    16,    17,    18,    31,    35,    36,
      37,    39,    48,    50,    55,    57,    60,    63,    66,    67,
      68,    71,    75,    36,    36,    13,    58,    59,    13,    64,
      65,    13,    61,    62,    13,    71,    71,    71,    76,    77,
      37,    71,    72,    49,    39,    39,    39,    21,    22,    23,
      24,    25,    23,    25,    11,    21,    22,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    38,    39,    71,    56,
      57,    60,    63,    71,    25,    42,    25,    42,    25,    42,
      51,    39,    42,    43,    13,    73,    74,    41,    41,    47,
      71,    71,    71,    71,    71,    71,    39,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    69,    70,    71,
      13,    41,    39,    71,    72,    58,    71,    64,    71,    61,
      36,    76,    44,    40,    42,    40,    43,    41,    42,    35,
      48,    71,    49,    71,    72,    73,    71,    71,     4,    39,
      13,    52,    53,    54,    43,    48,    71,    25,    41,    42,
      41,    71,    37,    54,    48,    47,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    49,    51,    50,
      52,    52,    53,    53,    54,    54,    55,    56,    56,    56,
      56,    57,    58,    58,    59,    59,    59,    60,    61,    61,
      62,    62,    63,    64,    64,    65,    66,    66,    67,    68,
      68,    68,    69,    69,    70,    70,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    72,    73,    73,    74,    74,    75,
      76,    77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     2,     2,     1,     1,
       3,     1,     3,     2,     1,     4,     1,     0,     0,    10,
       1,     0,     3,     1,     1,     3,     9,     1,     1,     1,
       1,     2,     3,     1,     1,     3,     3,     2,     3,     1,
       1,     3,     2,     3,     1,     3,     7,     5,     1,     4,
       3,     6,     1,     0,     3,     1,     0,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     4,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       1,     3,     1
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
#line 1505 "y.tab.c"
    break;

  case 3: /* CMDs: CMDs CMD  */
#line 137 "simbs.y"
                 { yyval.c = yyvsp[-1].c + yyvsp[0].c; }
#line 1511 "y.tab.c"
    break;

  case 4: /* CMDs: %empty  */
#line 138 "simbs.y"
                 { yyval.clear(); }
#line 1517 "y.tab.c"
    break;

  case 10: /* CMD: RETURN E ';'  */
#line 148 "simbs.y"
      { yyval.c = yyvsp[-1].c + "'&retorno'" + "@" + "~"; }
#line 1523 "y.tab.c"
    break;

  case 12: /* CMD: E ASM ';'  */
#line 152 "simbs.y"
                        { yyval.c = yyvsp[-2].c + yyvsp[-1].c + "^"; }
#line 1529 "y.tab.c"
    break;

  case 13: /* CMD: E ';'  */
#line 154 "simbs.y"
      { yyval.c = yyvsp[-1].c + "^"; }
#line 1535 "y.tab.c"
    break;

  case 14: /* CMD: ';'  */
#line 156 "simbs.y"
      { yyval.clear(); }
#line 1541 "y.tab.c"
    break;

  case 15: /* CMD: '{' EMPILHA_TS CMDs '}'  */
#line 158 "simbs.y"
      { ts.pop_back();
        yyval.c = vector<string>{"<{"} + yyvsp[-1].c + vector<string>{"}>"};  }
#line 1548 "y.tab.c"
    break;

  case 16: /* CMD: BLVAZIO  */
#line 161 "simbs.y"
      { yyval.clear(); }
#line 1554 "y.tab.c"
    break;

  case 17: /* EMPILHA_TS: %empty  */
#line 166 "simbs.y"
             { ts.push_back( map< string, Simbolo >{} ); }
#line 1560 "y.tab.c"
    break;

  case 18: /* $@1: %empty  */
#line 169 "simbs.y"
                       { declara_var( Var, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1566 "y.tab.c"
    break;

  case 19: /* CMD_FUNC: FUNCTION ID $@1 '(' EMPILHA_TS LISTA_ARGs ')' '{' CMDs '}'  */
#line 171 "simbs.y"
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
#line 1582 "y.tab.c"
    break;

  case 21: /* LISTA_ARGs: %empty  */
#line 186 "simbs.y"
             { yyval.clear(); }
#line 1588 "y.tab.c"
    break;

  case 22: /* ARGs: ARGs ',' ARG  */
#line 190 "simbs.y"
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
#line 1612 "y.tab.c"
    break;

  case 23: /* ARGs: ARG  */
#line 210 "simbs.y"
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
#line 1636 "y.tab.c"
    break;

  case 24: /* ARG: ID  */
#line 232 "simbs.y"
      { yyval.c = yyvsp[0].c;      
        yyval.n_args = 1;
        yyval.valor_default.clear();
        declara_var( Let, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); 
      }
#line 1646 "y.tab.c"
    break;

  case 25: /* ARG: ID '=' E  */
#line 238 "simbs.y"
      { // Código do IF
        yyval.c = yyvsp[-2].c;
        yyval.n_args = 1;
        yyval.valor_default = yyvsp[0].c;         
        declara_var( Let, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ); 
      }
#line 1657 "y.tab.c"
    break;

  case 26: /* CMD_FOR: FOR '(' PRIM_E ';' E ';' E ')' CMD  */
#line 247 "simbs.y"
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
#line 1675 "y.tab.c"
    break;

  case 30: /* PRIM_E: E  */
#line 266 "simbs.y"
         { yyval.c = yyvsp[0].c + "^"; }
#line 1681 "y.tab.c"
    break;

  case 31: /* CMD_LET: LET LET_VARs  */
#line 269 "simbs.y"
                       { yyval.c = yyvsp[0].c; }
#line 1687 "y.tab.c"
    break;

  case 32: /* LET_VARs: LET_VAR ',' LET_VARs  */
#line 272 "simbs.y"
                                { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1693 "y.tab.c"
    break;

  case 34: /* LET_VAR: ID  */
#line 277 "simbs.y"
          { yyval.c = declara_var( Let, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1699 "y.tab.c"
    break;

  case 35: /* LET_VAR: ID '=' E  */
#line 279 "simbs.y"
          { 
            yyval.c = declara_var( Let, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                   yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1707 "y.tab.c"
    break;

  case 36: /* LET_VAR: ID '=' OBJECT  */
#line 283 "simbs.y"
          { 
            yyval.c = declara_var( Let, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                   yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1715 "y.tab.c"
    break;

  case 37: /* CMD_VAR: VAR VAR_VARs  */
#line 288 "simbs.y"
                       { yyval.c = yyvsp[0].c; }
#line 1721 "y.tab.c"
    break;

  case 38: /* VAR_VARs: VAR_VAR ',' VAR_VARs  */
#line 291 "simbs.y"
                                { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1727 "y.tab.c"
    break;

  case 40: /* VAR_VAR: ID  */
#line 296 "simbs.y"
          { yyval.c = declara_var( Var, yyvsp[0].c[0], yyvsp[0].linha, yyvsp[0].coluna ); }
#line 1733 "y.tab.c"
    break;

  case 41: /* VAR_VAR: ID '=' E  */
#line 298 "simbs.y"
          {  yyval.c = declara_var( Var, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                    yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1740 "y.tab.c"
    break;

  case 42: /* CMD_CONST: CONST CONST_VARs  */
#line 302 "simbs.y"
                            { yyval.c = yyvsp[0].c; }
#line 1746 "y.tab.c"
    break;

  case 43: /* CONST_VARs: CONST_VAR ',' CONST_VARs  */
#line 305 "simbs.y"
                                      { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1752 "y.tab.c"
    break;

  case 45: /* CONST_VAR: ID '=' E  */
#line 310 "simbs.y"
            { yyval.c = declara_var( Const, yyvsp[-2].c[0], yyvsp[-2].linha, yyvsp[-2].coluna ) + 
                     yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1759 "y.tab.c"
    break;

  case 46: /* CMD_IF: IF '(' E ')' CMD ELSE CMD  */
#line 316 "simbs.y"
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
#line 1776 "y.tab.c"
    break;

  case 47: /* CMD_IF: IF '(' E ')' CMD  */
#line 329 "simbs.y"
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
#line 1792 "y.tab.c"
    break;

  case 49: /* LVALUEPROP: E '[' E ']'  */
#line 364 "simbs.y"
              { yyval.c = yyvsp[-3].c+ yyvsp[-1].c; }
#line 1798 "y.tab.c"
    break;

  case 50: /* LVALUEPROP: E '.' ID  */
#line 366 "simbs.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 1804 "y.tab.c"
    break;

  case 51: /* LVALUEPROP: E '.' ID '[' E ']'  */
#line 368 "simbs.y"
              { yyval.c = yyvsp[-5].c + yyvsp[-3].c + "[@]" + yyvsp[-1].c; }
#line 1810 "y.tab.c"
    break;

  case 53: /* LISTA_PARAMs: %empty  */
#line 372 "simbs.y"
             { yyval.clear(); }
#line 1816 "y.tab.c"
    break;

  case 54: /* PARAMs: PARAMs ',' E  */
#line 376 "simbs.y"
       { yyval.c = yyvsp[-2].c + yyvsp[0].c;
         yyval.n_args = yyvsp[-2].n_args + 1; }
#line 1823 "y.tab.c"
    break;

  case 55: /* PARAMs: E  */
#line 379 "simbs.y"
       { yyval.c = yyvsp[0].c;
         yyval.n_args = yyvsp[0].n_args + 1; }
#line 1830 "y.tab.c"
    break;

  case 57: /* E: LVALUE '=' E  */
#line 388 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[0].c + "="; }
#line 1836 "y.tab.c"
    break;

  case 58: /* E: LVALUEPROP '=' E  */
#line 390 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[0].c + "[=]"; }
#line 1842 "y.tab.c"
    break;

  case 59: /* E: LVALUE MAIS_IGUAL E  */
#line 396 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[-2].c + "@" + yyvsp[0].c + "+" + "="; }
#line 1848 "y.tab.c"
    break;

  case 60: /* E: LVALUEPROP MAIS_IGUAL E  */
#line 398 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + yyvsp[-2].c + "[@]" + yyvsp[0].c + "+" + "[=]"; }
#line 1854 "y.tab.c"
    break;

  case 61: /* E: LVALUE MAIS_MAIS  */
#line 400 "simbs.y"
    { checa_simbolo( yyvsp[-1].c[0], true ); yyval.c = yyvsp[-1].c + "@" + yyvsp[-1].c + yyvsp[-1].c + "@" + "1" + "+" + "=" + "^"; }
#line 1860 "y.tab.c"
    break;

  case 62: /* E: LVALUE IGUAL E  */
#line 402 "simbs.y"
    { checa_simbolo( yyvsp[-2].c[0], true ); yyval.c = yyvsp[-2].c + "@" + yyvsp[0].c + "==";}
#line 1866 "y.tab.c"
    break;

  case 63: /* E: LVALUE DIF E  */
#line 404 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "!="; }
#line 1872 "y.tab.c"
    break;

  case 64: /* E: E IGUAL E  */
#line 406 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "=="; }
#line 1878 "y.tab.c"
    break;

  case 65: /* E: E DIF E  */
#line 408 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + "!="; }
#line 1884 "y.tab.c"
    break;

  case 66: /* E: E '<' E  */
#line 410 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1890 "y.tab.c"
    break;

  case 67: /* E: E '>' E  */
#line 412 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1896 "y.tab.c"
    break;

  case 68: /* E: E '+' E  */
#line 414 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1902 "y.tab.c"
    break;

  case 69: /* E: E '-' E  */
#line 416 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1908 "y.tab.c"
    break;

  case 70: /* E: E '*' E  */
#line 418 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1914 "y.tab.c"
    break;

  case 71: /* E: E '/' E  */
#line 420 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1920 "y.tab.c"
    break;

  case 72: /* E: E '%' E  */
#line 422 "simbs.y"
    { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1926 "y.tab.c"
    break;

  case 73: /* E: '-' E  */
#line 424 "simbs.y"
    { yyval.c = "0" + yyvsp[0].c + yyvsp[-1].c; }
#line 1932 "y.tab.c"
    break;

  case 74: /* E: E '(' LISTA_PARAMs ')'  */
#line 426 "simbs.y"
    {
      yyval.c = yyvsp[-1].c + to_string( yyvsp[-1].n_args ) + yyvsp[-3].c + "$";
    }
#line 1940 "y.tab.c"
    break;

  case 75: /* E: CDOUBLE  */
#line 430 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1946 "y.tab.c"
    break;

  case 76: /* E: CINT  */
#line 432 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1952 "y.tab.c"
    break;

  case 77: /* E: CSTRING  */
#line 434 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1958 "y.tab.c"
    break;

  case 78: /* E: BOOL  */
#line 436 "simbs.y"
    { yyval.c = yyvsp[0].c; }
#line 1964 "y.tab.c"
    break;

  case 79: /* E: LVALUE  */
#line 439 "simbs.y"
    { if(!in_scope) checa_simbolo( yyvsp[0].c[0], false ); yyval.c = yyvsp[0].c + "@"; }
#line 1970 "y.tab.c"
    break;

  case 80: /* E: LVALUEPROP  */
#line 441 "simbs.y"
    { if(!in_scope) checa_simbolo( yyvsp[0].c[0], false ); yyval.c = yyvsp[0].c + "[@]"; }
#line 1976 "y.tab.c"
    break;

  case 81: /* E: '(' E ')'  */
#line 443 "simbs.y"
    { yyval.c = yyvsp[-1].c; }
#line 1982 "y.tab.c"
    break;

  case 82: /* E: '(' OBJECT ')'  */
#line 445 "simbs.y"
    { yyval.c = yyvsp[-1].c; }
#line 1988 "y.tab.c"
    break;

  case 84: /* OBJECT: '{' OBJECT_PROPs '}'  */
#line 454 "simbs.y"
           { yyval.c = "{}" + yyvsp[-1].c; }
#line 1994 "y.tab.c"
    break;

  case 85: /* OBJECT_PROP: ID ':' E  */
#line 458 "simbs.y"
               { yyval.c = yyvsp[-2].c + yyvsp[0].c + "[<=]"; }
#line 2000 "y.tab.c"
    break;

  case 86: /* OBJECT_PROP: ID ':' OBJECT  */
#line 460 "simbs.y"
               {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[<=]";}
#line 2006 "y.tab.c"
    break;

  case 87: /* OBJECT_PROPs: OBJECT_PROPs ',' OBJECT_PROP  */
#line 464 "simbs.y"
                 { yyval.c = yyvsp[-2].c + yyvsp[0].c; }
#line 2012 "y.tab.c"
    break;

  case 89: /* ARRAY: '[' ARRAY_ELEMs ']'  */
#line 469 "simbs.y"
          { yyval.c = "[]" + yyvsp[-1].c; }
#line 2018 "y.tab.c"
    break;

  case 91: /* ARRAY_ELEMs: ARRAY_ELEMs ',' ARRAY_ELEM  */
#line 476 "simbs.y"
               { yyval.c = yyvsp[-2].c + to_string( yyvsp[-2].n_args ) + yyvsp[0].c + "[<=]";
                yyval.n_args++; }
#line 2025 "y.tab.c"
    break;

  case 92: /* ARRAY_ELEMs: ARRAY_ELEM  */
#line 479 "simbs.y"
              { yyval.c = to_string( yyvsp[0].n_args ) + yyvsp[0].c + "[<=]";
                yyval.n_args++; }
#line 2032 "y.tab.c"
    break;


#line 2036 "y.tab.c"

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

#line 483 "simbs.y"


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

