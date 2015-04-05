/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

		#include "intermediate.h"
		#include "tcode.h"
		int yyerror (char* yaccProvidedMessage);
		int yylex(void);
		int scope,flag1,funcflag=0;
		enum SymbolTableType gType;
		extern unsigned int currQuad;
		extern int yylineno;
		extern char* yytext;
		extern FILE* yyin;
		int breakFlag=0;
		int funcInLoop=0;
		int conFlag=0;
		int loop = 0;
		int loopcounter=0;
		symTable Table;
		struct call{
			expr* elist;
			int method;
			char* name;
		};
		struct forVal{
			int test;
			int enter;
		};
		

#line 95 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    WHILE = 260,
    FOR = 261,
    FUNCTION = 262,
    RETURN = 263,
    BREAK = 264,
    CONTINUE = 265,
    AND = 266,
    OR = 267,
    NOT = 268,
    TRUE = 269,
    FALSE = 270,
    NIL = 271,
    INTEGER = 272,
    STRING = 273,
    REAL = 274,
    ID = 275,
    LOCAL = 276,
    LBRACKET = 277,
    RBRACKET = 278,
    LTAB = 279,
    RTAB = 280,
    LPAR = 281,
    RPAR = 282,
    SEMICOLON = 283,
    COMMA = 284,
    COLON = 285,
    DCOLON = 286,
    FULLSTOP = 287,
    DOTDOT = 288,
    COMMENT_1 = 289,
    COMMENT_2 = 290,
    COMMENT_ERROR = 291,
    ERROR = 292,
    ASSIGNMENT = 293,
    MULTI = 294,
    DIV = 295,
    MOD = 296,
    EQUAL = 297,
    NEQUAL = 298,
    PLUSPLUS = 299,
    MINUSMINUS = 300,
    GREATER = 301,
    LESS = 302,
    GREATEROREQ = 303,
    LESSOREQ = 304,
    NEWLINE = 305,
    NEWTAB = 306,
    PLUS = 307,
    MINUS = 308,
    UMINUS = 309
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define RETURN 263
#define BREAK 264
#define CONTINUE 265
#define AND 266
#define OR 267
#define NOT 268
#define TRUE 269
#define FALSE 270
#define NIL 271
#define INTEGER 272
#define STRING 273
#define REAL 274
#define ID 275
#define LOCAL 276
#define LBRACKET 277
#define RBRACKET 278
#define LTAB 279
#define RTAB 280
#define LPAR 281
#define RPAR 282
#define SEMICOLON 283
#define COMMA 284
#define COLON 285
#define DCOLON 286
#define FULLSTOP 287
#define DOTDOT 288
#define COMMENT_1 289
#define COMMENT_2 290
#define COMMENT_ERROR 291
#define ERROR 292
#define ASSIGNMENT 293
#define MULTI 294
#define DIV 295
#define MOD 296
#define EQUAL 297
#define NEQUAL 298
#define PLUSPLUS 299
#define MINUSMINUS 300
#define GREATER 301
#define LESS 302
#define GREATEROREQ 303
#define LESSOREQ 304
#define NEWLINE 305
#define NEWTAB 306
#define PLUS 307
#define MINUS 308
#define UMINUS 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 30 "parser.y" /* yacc.c:355  */

	char* stringValue;
	int   intValue;
	double realValue;
	struct expr* exprValue;
	struct forVal* forValue;
	struct symbol* symValue;
	struct call* callValue;
	

#line 254 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 271 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   559

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    79,    79,    80,    84,    85,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   104,   116,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   172,   205,   206,   212,   220,   242,   265,   287,
     312,   314,   343,   344,   345,   346,   349,   352,   411,   458,
     475,   480,   483,   489,   491,   497,   500,   500,   529,   541,
     542,   546,   554,   562,   594,   598,   613,   615,   616,   621,
     634,   655,   675,   692,   696,   706,   706,   710,   711,   716,
     730,   730,   746,   751,   768,   794,   803,   804,   805,   806,
     807,   811,   812,   816,   842,   846,   869,   874,   910,   915,
     928,   935,   971,   977,   987,   987,  1005,  1012,  1014,  1017,
    1018,  1019,  1021,  1024,  1025
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "RETURN", "BREAK", "CONTINUE", "AND", "OR", "NOT", "TRUE", "FALSE",
  "NIL", "INTEGER", "STRING", "REAL", "ID", "LOCAL", "LBRACKET",
  "RBRACKET", "LTAB", "RTAB", "LPAR", "RPAR", "SEMICOLON", "COMMA",
  "COLON", "DCOLON", "FULLSTOP", "DOTDOT", "COMMENT_1", "COMMENT_2",
  "COMMENT_ERROR", "ERROR", "ASSIGNMENT", "MULTI", "DIV", "MOD", "EQUAL",
  "NEQUAL", "PLUSPLUS", "MINUSMINUS", "GREATER", "LESS", "GREATEROREQ",
  "LESSOREQ", "NEWLINE", "NEWTAB", "PLUS", "MINUS", "UMINUS", "$accept",
  "program", "stmts", "stmt", "break", "continue", "expr", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "$@1", "callsuffix",
  "normcall", "methodcall", "elist", "elist2", "objectdef", "objectdef1",
  "objectdef2", "indexed", "indexed2", "indexedelem", "block", "$@2",
  "block2", "funcdef", "funcprefix", "$@3", "funcargs", "funcbody",
  "funcname", "const", "number", "idlist", "idlist2", "ifstmt", "ifprefix",
  "elseprefix", "while", "whilestart", "whilecond", "for", "$@4",
  "forprefix", "N", "M", "loopstmt", "loopstart", "loopend", "returnstmt",
  "returnstmt2", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -173

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-173)))

#define YYTABLE_NINF -57

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-57)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,   -24,  -173,   -18,  -173,   506,   -11,    13,   506,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,    24,  -173,   465,   169,
    -173,    25,     9,     9,   506,    33,   122,  -173,  -173,  -173,
     187,  -173,  -173,  -173,   -17,  -173,    -6,  -173,  -173,  -173,
    -173,  -173,    23,  -173,  -173,  -173,   122,  -173,    26,  -173,
    -173,  -173,   506,   506,    30,   406,    28,  -173,  -173,  -173,
    -173,   122,   506,   208,    29,    34,    31,   231,    35,  -173,
      51,    10,    -6,    10,  -173,  -173,  -173,   506,   506,  -173,
     506,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   506,    41,   506,  -173,  -173,     6,   506,   506,    43,
      44,    45,    61,   506,  -173,   506,   254,    38,  -173,  -173,
    -173,   122,    46,   274,   506,  -173,  -173,  -173,    48,  -173,
    -173,    42,    47,   459,   424,  -173,  -173,  -173,   500,   500,
      55,    55,    55,    55,   -29,   -29,   299,  -173,   406,   506,
      69,  -173,  -173,  -173,   318,    63,  -173,    62,    70,  -173,
    -173,  -173,   122,   342,  -173,   122,    72,  -173,  -173,  -173,
    -173,   506,   208,    31,   506,    42,  -173,    78,    80,  -173,
    -173,    90,  -173,  -173,  -173,  -173,  -173,  -173,  -173,   506,
     363,  -173,  -173,    84,  -173,   506,    62,  -173,  -173,   385,
    -173,  -173,    86,  -173,  -173,  -173,  -173,  -173,  -173
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,   102,     0,    80,   114,     0,     0,     0,    89,
      90,    88,    91,    87,    92,    47,     0,    75,    64,     0,
      15,     0,     0,     0,     0,     0,     2,     4,    13,    14,
       0,    19,    18,    40,    43,    50,    42,    44,    67,    68,
      11,    12,     0,    46,    86,     7,     0,     8,     0,     9,
     107,    10,     0,    64,    85,   113,     0,    16,    17,    35,
      48,    78,     0,    66,     0,     0,    73,     0,     0,    49,
       0,    36,     0,    38,    34,     1,     5,     0,     0,     6,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,    39,     0,     0,    64,     0,
      94,     0,    98,     0,   110,    64,     0,     0,    84,    81,
     112,    78,     0,     0,     0,    63,    69,    70,     0,    71,
      33,    45,     0,    31,    32,    22,    23,    24,    29,    30,
      25,    27,    26,    28,    20,    21,     0,    51,    41,    64,
       0,    57,    59,    60,     0,     0,    53,    96,     0,    83,
      79,   100,     0,     0,   108,     0,     0,    99,   108,    77,
      76,     0,    66,    73,    64,     0,    52,     0,     0,    54,
      55,     0,    93,    82,    97,   103,   101,   111,   107,     0,
       0,    65,    72,     0,    61,    64,    96,   109,   104,     0,
      74,    58,     0,    95,   110,   106,    62,   107,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,     5,  -173,  -173,    -5,  -173,  -173,  -173,
       0,  -173,    15,  -173,  -173,  -173,  -173,   -52,   -91,  -173,
    -173,  -173,  -173,   -49,    -3,    16,  -173,     7,   -15,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,   -70,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,  -173,  -173,  -172,   -39,   -74,
    -173,  -173,  -173,  -173
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,   111,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    96,   141,   142,   143,    64,   115,    37,
      38,    39,    65,   119,    66,    40,    61,   112,    41,    42,
      54,   101,   150,   109,    43,    44,   148,   172,    45,    46,
     152,    47,    48,   104,    49,   194,    50,   105,   176,   154,
     155,   187,    51,    56
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,   107,    52,    59,    68,    27,   188,    91,    53,   -56,
      80,    81,    82,    63,    67,    92,   -56,    57,    97,    74,
      98,    93,    71,    73,    90,   198,    99,    94,    95,    15,
      16,    76,   139,    75,    91,    70,   -56,    72,    72,   140,
      21,    58,    92,   -56,    60,    69,   145,   106,    63,   100,
     108,   102,   103,   156,   116,   122,   110,   113,     4,   117,
     118,   137,   121,   146,   147,   151,   158,    17,   164,   160,
      62,   181,   123,   124,   165,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   167,   138,   168,
     170,   171,   144,    63,    80,    81,    82,   173,   153,   178,
      63,   -57,   -57,   -57,   -57,   184,   185,    89,    90,   162,
     186,   191,   183,   196,   182,   163,   193,   149,   159,   179,
     197,     0,     0,     0,     0,     1,     0,     2,     3,     4,
       5,     6,     7,   192,    63,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,    18,     0,    19,     0,
      20,     0,     0,    21,     0,     0,   180,   174,     0,    63,
     177,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,     0,     0,   189,    24,     4,     0,     0,     0,
      63,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,     0,     0,    18,     0,    19,     0,     0,    77,    78,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    22,    23,    79,     0,     0,     0,    77,
      78,     0,    24,     0,     0,     0,    80,    81,    82,    83,
      84,     0,     0,    85,    86,    87,    88,   114,     0,    89,
      90,     0,    77,    78,     0,     0,     0,    80,    81,    82,
      83,    84,     0,     0,    85,    86,    87,    88,   120,     0,
      89,    90,     0,     0,     0,    77,    78,     0,     0,     0,
      80,    81,    82,    83,    84,     0,     0,    85,    86,    87,
      88,   157,     0,    89,    90,    77,    78,     0,     0,     0,
       0,     0,     0,    80,    81,    82,    83,    84,     0,     0,
      85,    86,    87,    88,   161,     0,    89,    90,     0,     0,
      77,    78,     0,    80,    81,    82,    83,    84,     0,     0,
      85,    86,    87,    88,   166,     0,    89,    90,     0,    77,
      78,     0,     0,     0,     0,     0,     0,     0,    80,    81,
      82,    83,    84,   169,     0,    85,    86,    87,    88,     0,
       0,    89,    90,    77,    78,     0,     0,    80,    81,    82,
      83,    84,     0,     0,    85,    86,    87,    88,     0,   175,
      89,    90,     0,     0,    77,    78,     0,     0,     0,     0,
       0,    80,    81,    82,    83,    84,   190,     0,    85,    86,
      87,    88,     0,     0,    89,    90,    77,    78,     0,     0,
       0,     0,    80,    81,    82,    83,    84,     0,     0,    85,
      86,    87,    88,   195,     0,    89,    90,    77,    78,     0,
       0,     0,     0,     0,    80,    81,    82,    83,    84,     0,
       0,    85,    86,    87,    88,    77,     0,    89,    90,     0,
       0,     0,     0,     0,     0,    80,    81,    82,    83,    84,
       0,     0,    85,    86,    87,    88,     0,     0,    89,    90,
       0,     0,     0,    80,    81,    82,    83,    84,     0,     0,
      85,    86,    87,    88,     0,     0,    89,    90,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    62,     0,    18,
       0,    19,     0,     0,     0,     0,    21,     0,    80,    81,
      82,    83,    84,     0,     0,    85,    86,    87,    88,    22,
      23,    89,    90,     0,     0,     0,     0,     0,    24,     8,
       9,    10,    11,    12,    13,    14,    15,    16,     0,     0,
      18,     0,    19,     0,     0,     0,     0,    21,     0,    80,
      81,    82,   -57,   -57,     0,     0,    85,    86,    87,    88,
      22,    23,    89,    90,     0,     0,     0,     0,     0,    24
};

static const yytype_int16 yycheck[] =
{
       5,    53,    26,     8,    19,     0,   178,    24,    26,    26,
      39,    40,    41,    18,    19,    32,    33,    28,    24,    24,
      26,    38,    22,    23,    53,   197,    32,    44,    45,    20,
      21,    26,    26,     0,    24,    26,    26,    22,    23,    33,
      31,    28,    32,    33,    20,    20,    98,    52,    53,    26,
      20,    46,    26,   105,    25,    70,    28,    62,     7,    25,
      29,    20,    27,    20,    20,     4,    28,    22,    26,    23,
      22,   162,    77,    78,    27,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,   139,    93,    20,
      27,    29,    97,    98,    39,    40,    41,    27,   103,    27,
     105,    46,    47,    48,    49,    27,    26,    52,    53,   114,
      20,    27,   164,    27,   163,   118,   186,   101,   111,   158,
     194,    -1,    -1,    -1,    -1,     3,    -1,     5,     6,     7,
       8,     9,    10,   185,   139,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    -1,    26,    -1,
      28,    -1,    -1,    31,    -1,    -1,   161,   152,    -1,   164,
     155,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,   179,    53,     7,    -1,    -1,    -1,
     185,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    -1,    -1,    24,    -1,    26,    -1,    -1,    11,    12,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    28,    -1,    -1,    -1,    11,
      12,    -1,    53,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    -1,    -1,    46,    47,    48,    49,    29,    -1,    52,
      53,    -1,    11,    12,    -1,    -1,    -1,    39,    40,    41,
      42,    43,    -1,    -1,    46,    47,    48,    49,    27,    -1,
      52,    53,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    -1,    -1,    46,    47,    48,
      49,    27,    -1,    52,    53,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    30,    -1,    52,    53,    -1,    -1,
      11,    12,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    25,    -1,    52,    53,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    43,    25,    -1,    46,    47,    48,    49,    -1,
      -1,    52,    53,    11,    12,    -1,    -1,    39,    40,    41,
      42,    43,    -1,    -1,    46,    47,    48,    49,    -1,    27,
      52,    53,    -1,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    43,    23,    -1,    46,    47,
      48,    49,    -1,    -1,    52,    53,    11,    12,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    -1,    -1,    46,
      47,    48,    49,    28,    -1,    52,    53,    11,    12,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,    -1,
      -1,    46,    47,    48,    49,    11,    -1,    52,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    43,
      -1,    -1,    46,    47,    48,    49,    -1,    -1,    52,    53,
      -1,    -1,    -1,    39,    40,    41,    42,    43,    -1,    -1,
      46,    47,    48,    49,    -1,    -1,    52,    53,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    -1,    24,
      -1,    26,    -1,    -1,    -1,    -1,    31,    -1,    39,    40,
      41,    42,    43,    -1,    -1,    46,    47,    48,    49,    44,
      45,    52,    53,    -1,    -1,    -1,    -1,    -1,    53,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    26,    -1,    -1,    -1,    -1,    31,    -1,    39,
      40,    41,    42,    43,    -1,    -1,    46,    47,    48,    49,
      44,    45,    52,    53,    -1,    -1,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    24,    26,
      28,    31,    44,    45,    53,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    74,    75,    76,
      80,    83,    84,    89,    90,    93,    94,    96,    97,    99,
     101,   107,    26,    26,    85,    61,   108,    28,    28,    61,
      20,    81,    22,    61,    72,    77,    79,    61,    83,    20,
      26,    65,    67,    65,    61,     0,    58,    11,    12,    28,
      39,    40,    41,    42,    43,    46,    47,    48,    49,    52,
      53,    24,    32,    38,    44,    45,    68,    24,    26,    32,
      26,    86,    58,    26,    98,   102,    61,    72,    20,    88,
      28,    58,    82,    61,    29,    73,    25,    25,    29,    78,
      27,    27,    83,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    20,    61,    26,
      33,    69,    70,    71,    61,    72,    20,    20,    91,    80,
      87,     4,    95,    61,   104,   105,    72,    27,    28,    82,
      23,    30,    61,    79,    26,    27,    25,    72,    20,    25,
      27,    29,    92,    27,    58,    27,   103,    58,    27,   103,
      61,    73,    78,    72,    27,    26,    20,   106,   102,    61,
      23,    27,    72,    92,   100,    28,    27,   104,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    59,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    63,    64,    64,    64,    64,    64,    65,    65,    65,
      65,    66,    66,    66,    66,    67,    68,    67,    67,    69,
      69,    70,    71,    72,    72,    73,    73,    74,    74,    75,
      76,    77,    78,    78,    79,    81,    80,    82,    82,    83,
      85,    84,    86,    87,    88,    88,    89,    89,    89,    89,
      89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
      95,    96,    97,    98,   100,    99,   101,   102,   103,   104,
     105,   106,   107,   108,   108
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     0,     3,     6,     1,
       1,     3,     5,     2,     0,     3,     0,     1,     1,     3,
       3,     2,     3,     0,     5,     0,     4,     2,     0,     3,
       0,     3,     3,     1,     1,     0,     1,     1,     1,     1,
       1,     1,     1,     2,     0,     3,     0,     4,     2,     4,
       1,     4,     1,     3,     0,     8,     7,     0,     0,     3,
       0,     0,     3,     1,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 3:
#line 80 "parser.y" /* yacc.c:1646  */
    {printf("empty statement \n");}
#line 1571 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 84 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = (expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);puts("STMT");}
#line 1577 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 85 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = (expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);
					if((yyvsp[-1].exprValue)->breaklist){(yyval.exprValue)->breaklist = merge((yyvsp[-1].exprValue)->breaklist,(yyvsp[0].exprValue)->breaklist);}
					if((yyvsp[-1].exprValue)->conlist){(yyval.exprValue)->conlist = merge((yyvsp[-1].exprValue)->conlist,(yyvsp[0].exprValue)->conlist);}
}
#line 1586 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 92 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[-1].exprValue);resetTemp();printf("some expression\n");}
#line 1592 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 93 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("IF statement\n");}
#line 1598 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 94 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("While statement\n");}
#line 1604 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 95 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("For statement\n");}
#line 1610 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 96 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("Return statement\n");}
#line 1616 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 97 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("in BLOCK\n");}
#line 1622 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 98 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=lvalue_expr((yyvsp[0].exprValue)->sym);resetTemp();printf("function definition\n");/*funcflag--;*/}
#line 1628 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 99 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("BREAK\n");}
#line 1634 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 100 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);resetTemp();printf("CONTINUE\n");}
#line 1640 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 101 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));resetTemp();printf("SEMICOLON\n");}
#line 1646 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 105 "parser.y" /* yacc.c:1646  */
    {if((funcflag==0 && funcInLoop ==0)||(funcflag>0 && funcInLoop==1)){
		if(loopcounter>0){
			breakFlag++;
			(yyval.exprValue)=(expr*)malloc(sizeof(expr));
			(yyval.exprValue)->conlist = NULL;
			(yyval.exprValue)->breaklist = newlist(nextquadlabel());
			emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			else{puts("error : NOT IN LOOP");}}else puts("Cannot use break without a loop ERROR.");
}
#line 1661 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 117 "parser.y" /* yacc.c:1646  */
    {if((funcflag==0 && funcInLoop ==0)||(funcflag>0 && funcInLoop==1)){
		if(loopcounter>0){
			conFlag++;
			(yyval.exprValue)=(expr*)malloc(sizeof(expr));
			(yyval.exprValue)->conlist = newlist(nextquadlabel());
			(yyval.exprValue)->breaklist = NULL;
			emit(jump,NULL,NULL,NULL,0,yylineno);
			}
			else{puts("error : NOT IN LOOP");}}else puts("Cannot use continue without a loop ERROR.");
}
#line 1676 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 128 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);printf("assignment expression\n");}
#line 1682 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 129 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);printf("term\n");}
#line 1688 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 130 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=op_expr(Table,add,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr + expr\n");}
#line 1694 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 131 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=op_expr(Table,sub,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr - expr\n");}
#line 1700 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 132 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=op_expr(Table,mul,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr * expr\n");}
#line 1706 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 133 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=op_expr(Table,divi,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr / expr\n");}
#line 1712 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 134 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=op_expr(Table,mod,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr MOD expr\n");}
#line 1718 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 135 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_greater,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr > expr\n");}
#line 1724 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 136 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_greatereq,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr >= expr\n");}
#line 1730 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 137 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_less,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr < expr\n");}
#line 1736 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 138 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_lesseq,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr <= expr\n");}
#line 1742 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 139 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_eq,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr == expr\n");}
#line 1748 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 140 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=bool_expr(Table,if_noteq,(yyvsp[-2].exprValue),(yyvsp[0].exprValue));printf("expr != expr\n");}
#line 1754 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 141 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);
						if((yyvsp[-2].exprValue) && (yyvsp[0].exprValue) && (yyvsp[-2].exprValue)->type!=5){
							(yyvsp[0].exprValue)->truelist = merge((yyvsp[-2].exprValue)->falselist,(yyvsp[0].exprValue)->falselist);
						}
						if((yyvsp[-2].exprValue)->type!=5){
							(yyvsp[-2].exprValue) = bool_expr(Table,if_eq,(yyvsp[-2].exprValue),newexpr_constbool('1'));
						}


						if((yyvsp[0].exprValue)){
							(yyval.exprValue)->falselist = merge((yyvsp[-2].exprValue)->falselist,(yyvsp[0].exprValue)->falselist);
						}
						else{
							(yyval.exprValue)->falselist = (yyvsp[-2].exprValue)->falselist;
						}
						struct list* temp = NULL;
						temp = (yyval.exprValue)->falselist;

						/*if($3->type!=5){
							while((temp)){
								patchlabel(temp->label,nextquadlabel()+2);
								temp = temp->next;							}						  
						}*/

						while(temp){	
							patchlabel(temp->label,nextquadlabel()+1);
							temp = temp->next;
						}
						(yyval.exprValue)->truelist = (yyvsp[0].exprValue)->truelist;
						
					}
#line 1790 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 172 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = (yyvsp[0].exprValue);
						if((yyvsp[-2].exprValue) && (yyvsp[0].exprValue) && (yyvsp[-2].exprValue)->type!=5){
							(yyvsp[0].exprValue)->truelist = merge((yyvsp[-2].exprValue)->truelist,(yyvsp[0].exprValue)->truelist);
						}
						if((yyvsp[-2].exprValue)->type!=5){
							(yyvsp[-2].exprValue) = bool_expr(Table,if_eq,(yyvsp[-2].exprValue),newexpr_constbool('1'));
						}
						if((yyvsp[0].exprValue)){
							(yyval.exprValue)->truelist = merge((yyvsp[-2].exprValue)->truelist,(yyvsp[0].exprValue)->truelist);
						}
						else{
							(yyval.exprValue)->truelist = (yyvsp[-2].exprValue)->truelist;
						}
						struct list* temp = NULL;
						temp = (yyval.exprValue)->truelist;	
					
						if((yyvsp[0].exprValue)->type!=5){
							while((temp)){
								patchlabel(temp->label,nextquadlabel()+2);
								temp = temp->next;							}						  
						}
						else{
							while((temp)){
								patchlabel(temp->label,nextquadlabel()-1);
								temp = temp->next;
							}
						}
						(yyval.exprValue)->falselist = (yyvsp[0].exprValue)->falselist;
												
					}
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 205 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[-1].exprValue);printf("(expression) \n");}
#line 1831 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 206 "parser.y" /* yacc.c:1646  */
    {
						checkuminus((yyvsp[0].exprValue));
						(yyval.exprValue) = newexpr(arithmexpr_e);
						(yyval.exprValue)->sym = newtemp(Table);
						emit(uminus,(yyvsp[0].exprValue),NULL,(yyval.exprValue),-1,yylineno);
						printf("-expression");}
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 212 "parser.y" /* yacc.c:1646  */
    {
						(yyval.exprValue)=newexpr(boolexpr_e);
						(yyval.exprValue)->sym = newtemp(Table);
						emit(not,(yyvsp[0].exprValue),NULL,(yyval.exprValue),-1,yylineno);
						(yyval.exprValue)->truelist = (yyvsp[0].exprValue)->falselist;
						(yyval.exprValue)->falselist = (yyvsp[0].exprValue)->truelist;
						printf("!expression \n");
					}
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 220 "parser.y" /* yacc.c:1646  */
    {
						const char * val;
						val = (yyvsp[0].exprValue)->sym->name;		//TODO:lvalue_expr sta parakatw
						if((yyvsp[0].exprValue)->type == tableitem_e){ 
							(yyval.exprValue) = emit_iftableitem((yyvsp[0].exprValue));
							emit(add,(yyval.exprValue),newexpr_constnum(1),(yyval.exprValue),-1,yylineno);
							emit(tablesetelem,(yyvsp[0].exprValue),(yyvsp[0].exprValue)->index,(yyval.exprValue),-1,yylineno);
						}																					
						else{
							emit(add,(yyvsp[0].exprValue),newexpr_constnum(1),(yyvsp[0].exprValue),-1,yylineno);
							(yyval.exprValue)=newexpr(arithmexpr_e);
							(yyval.exprValue)->sym = newtemp(Table);
							(yyval.exprValue)=lvalue_expr((yyval.exprValue)->sym);
							emit(assign,(yyvsp[0].exprValue),NULL,(yyval.exprValue),-1,yylineno);
						}
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);	
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR: cant ++ a func\n");
						}
						printf("++lvalue \n");
					}
#line 1882 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 242 "parser.y" /* yacc.c:1646  */
    {	
						(yyval.exprValue)=newexpr(var_e);
						(yyval.exprValue)->sym = newtemp(Table);
						expr* value;
						if((yyvsp[-1].exprValue)->type == tableitem_e){
							value = emit_iftableitem((yyvsp[-1].exprValue));
							emit(assign,value,NULL,(yyval.exprValue),-1,yylineno);
							emit(add,value,newexpr_constnum(1),value,-1,yylineno);
							emit(tablesetelem,(yyvsp[-1].exprValue),(yyvsp[-1].exprValue)->index,value,-1,yylineno);
						}
						 						
						else{
						
							emit(assign,(yyvsp[-1].exprValue),NULL,(yyval.exprValue),-1,yylineno);
							emit(add,(yyvsp[-1].exprValue),newexpr_constnum(1),(yyvsp[-1].exprValue),-1,yylineno);
						}						const char * val;val = (yyvsp[-1].exprValue)->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR:cant func ++\n");
						}
						printf("lvalue++ \n");}
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 265 "parser.y" /* yacc.c:1646  */
    {
						if((yyvsp[0].exprValue)->type == tableitem_e){ 
							(yyval.exprValue) = emit_iftableitem((yyvsp[0].exprValue));
							emit(sub,(yyval.exprValue),newexpr_constnum(1),(yyval.exprValue),-1,yylineno);
							emit(tablesetelem,(yyvsp[0].exprValue),(yyvsp[0].exprValue)->index,(yyval.exprValue),-1,yylineno);
							}
							
							else{

							emit(sub,(yyvsp[0].exprValue),newexpr_constnum(1),(yyvsp[0].exprValue),-1,yylineno);
							(yyval.exprValue)=newexpr(arithmexpr_e);
							(yyval.exprValue)->sym = newtemp(Table);
							emit(assign,(yyvsp[0].exprValue),NULL,(yyval.exprValue),-1,yylineno);
							}
						const char * val;val = (yyvsp[0].exprValue)->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR\n");
						}
						printf("--lvalue \n");
					}
#line 1936 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 287 "parser.y" /* yacc.c:1646  */
    {

						(yyval.exprValue)=newexpr(var_e);
						(yyval.exprValue)->sym = newtemp(Table);
						expr* value;
						 if((yyvsp[-1].exprValue)->type == tableitem_e){
							value = emit_iftableitem((yyvsp[-1].exprValue));
							emit(assign,value,NULL,(yyval.exprValue),-1,yylineno);
							emit(sub,value,newexpr_constnum(1),value,-1,yylineno);
							emit(tablesetelem,(yyvsp[-1].exprValue),(yyvsp[-1].exprValue)->index,value,-1,yylineno);
						}

						
						else{
						
							emit(assign,(yyvsp[-1].exprValue),NULL,(yyval.exprValue),-1,yylineno);
							emit(sub,(yyvsp[-1].exprValue),newexpr_constnum(1),(yyvsp[-1].exprValue),-1,yylineno);
						}
						const char * val;val = (yyvsp[-1].exprValue)->sym->name;
						SymbolTableEntry * temp=NULL;
						temp = lookUpScope(Table,val,USERFUNC,scope);
						if(temp){
							if(temp->type==USERFUNC)printf("ERROR\n");
						}
						printf("lvalue-- \n");}
#line 1966 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 312 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);printf("primary \n");}
#line 1972 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 314 "parser.y" /* yacc.c:1646  */
    {

			if((yyvsp[-2].exprValue)->type == tableitem_e){
				emit(tablesetelem,(yyvsp[-2].exprValue),(yyvsp[-2].exprValue)->index,(yyvsp[0].exprValue),-1,yylineno);
				(yyval.exprValue)=emit_iftableitem((yyvsp[-2].exprValue));
				(yyval.exprValue)->type = assignexpr_e;
			}
			else{
				emit(assign,(yyvsp[0].exprValue),NULL,(yyvsp[-2].exprValue),-1,yylineno);
				(yyval.exprValue)=newexpr(assignexpr_e);
				(yyval.exprValue)->sym = newtemp(Table);
				emit(assign,(yyvsp[-2].exprValue),NULL,(yyval.exprValue),-1,yylineno);
			}
			if(!(yyvsp[-2].exprValue)->sym){
				printf("Den uparxei symbol    ERROR\n");
			}

			const char * val;val = (yyvsp[-2].exprValue)->sym->name;
			SymbolTableEntry * temp=NULL;
			temp = lookUpScope(Table,val,USERFUNC,scope);
			if(temp){
				if(temp->type==USERFUNC)printf("ERROR\n");
				else{
					printf("Result of assign : %s \n",(yyvsp[-2].exprValue)->sym->name);
				}
			}
		}
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 343 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);flag1=0;printf("call \n");}
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 344 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = emit_iftableitem((yyvsp[0].exprValue));printf("lvalue \n");}
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 345 "parser.y" /* yacc.c:1646  */
    {printf("object definition \n");(yyval.exprValue) = (yyvsp[0].exprValue);}
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 346 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = newexpr(programfunc_e);
					 (yyval.exprValue)->sym = (yyvsp[-1].exprValue)->sym;
					 printf("(function definition) \n");}
#line 2030 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 349 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue); printf("constant \n");}
#line 2036 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 352 "parser.y" /* yacc.c:1646  */
    {		
						const char* val = (yyvsp[0].stringValue);struct symbol * sym = NULL;SymbolTableEntry *temp=NULL;
									if(lookUp(Table,val)==0){
										sym = newSymbol((yyvsp[0].stringValue));
										sym->space = currscopespace();
										sym->offset = currscopeoffset();
										inccurrscopeoffset();
										(yyval.exprValue) = lvalue_expr(sym);
										if(scope>0) {insert(Table,val,LOCALS,yylineno,scope);printf("new local id\n");}//use look up,make/reuse symbol,make lvalue
										else  {
											insert(Table,val,GLOBAL,yylineno,scope);printf("new global id\n");}
										temp = lookUpScope(Table,val,GLOBAL,scope);
										temp->sym = sym;
									}
									else{
											int i;
											temp = lookUpScope(Table,val,LOCALS,scope);
											for(i=scope;i>=0 && funcflag==0;i--){
												temp = lookUpScope(Table,val,LOCALS,i);
												if(temp){break;}
											}
											if(funcflag>0){
												/*temp = lookUpScope(Table,val,FORMAL,scope-1);
												if(!(temp->sym->type == FORMAL)){temp=NULL;}*/
											}
											if(!temp){
												temp = lookUpScope(Table,val,GLOBAL,0);
												if(!temp){
													printf("Cannot Access Value: %s\n",val);
												}
												else if(funcflag>0 && temp->type!=LIBFUNC && temp->type!=USERFUNC){(yyval.exprValue)=lvalue_expr(temp->sym);
													printf("Cannot Access %s in function ERROR\n",val);
													}
												else{(yyval.exprValue)=lvalue_expr(temp->sym);printf("%s - Found Globaly.\n",val);}
											}
											//else if(temp->type == LIBFUNC){printf("library function collision: %s\n",temp->cat.varVal->value);}
											//else if (temp->type == USERFUNC){printf("user function collision: %s\n",temp->cat.varVal->value);}
											else{
												if(!temp->sym){
													printf("%s Gamaei tw 8ew.     %d \n",val,yylineno);
													
												}
												else if(temp->sym->line==yylineno){
													//printf("var %s was undefined before this line ERROR\n",temp->sym->name);
												}
												(yyval.exprValue)=lvalue_expr(temp->sym);
												//printf("%s - Found in same scope.\n",val);
											} 
												
											
																				
									}
						}
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 411 "parser.y" /* yacc.c:1646  */
    {	
						
						const char *val=(yyvsp[0].stringValue);
						struct symbol * sym =NULL; 
						SymbolTableEntry *temp=NULL;
						if(scope>0){
							
							if(lookUp(Table,val)==1)
								temp = lookUpScope(Table,val,LOCALS,scope);
							if(temp){
								if(temp->type == USERFUNC){
									printf("user function collision: %s\n",temp->cat.varVal->value);
								}
								else{
									printf("%s - Found localy\n",val);
									(yyval.exprValue) =lvalue_expr(temp->sym);
								}
							}
							else{
								sym = newSymbol((yyvsp[0].stringValue));
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								inccurrscopeoffset();
								insert(Table,val,LOCALS,yylineno,scope);
								temp = lookUpScope(Table,val,LOCALS,scope);
								temp->sym = sym;
								(yyval.exprValue)= lvalue_expr(temp->sym);
							}
							printf("local id \n");
						}
						else{
							if(lookUp(Table,val)==0){insert(Table,val,GLOBAL,yylineno,0);
								sym = newSymbol((yyvsp[0].stringValue));
								sym->space = currscopespace();
								sym->offset = currscopeoffset();
								inccurrscopeoffset();
								temp = lookUpScope(Table,val,GLOBAL,0);
								temp->sym = sym;
								if(temp->sym){printf("clein2\n");}
								(yyval.exprValue)= lvalue_expr(temp->sym);}
							else{printf("%s - Found Globally.\n",val);
								temp = lookUpScope(Table,val,GLOBAL,0);
								(yyval.exprValue) = lvalue_expr(temp->sym);
							}
						}
					}
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 458 "parser.y" /* yacc.c:1646  */
    {		
						const char* val=(yyvsp[0].stringValue); 
						if (lookUp(Table,val)== 0){
							printf("no %s as global variable\n",val);	
						}
						else{
							SymbolTableEntry *temp;
							temp = lookUpScope(Table,val,GLOBAL,0);
							if(temp == NULL){
								printf("no %s as global variable\n",val);
							}
							else{
								printf("Global variable %s found\n",val);
							}
						(yyval.exprValue)=lvalue_expr(temp->sym);
						printf("::id \n");}
					}
#line 2167 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 475 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);printf("member \n");
					}
#line 2174 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 480 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = member_item((yyvsp[-2].exprValue),(yyvsp[0].stringValue));
					printf("lvalue.id \n");}
#line 2182 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 483 "parser.y" /* yacc.c:1646  */
    {
					(yyvsp[-3].exprValue) = emit_iftableitem((yyvsp[-3].exprValue));
					(yyval.exprValue) = newexpr(tableitem_e);
					(yyval.exprValue)->sym = (yyvsp[-3].exprValue)->sym;
					(yyval.exprValue)->index = (yyvsp[-1].exprValue);
					printf("lvalue[expression] \n");}
#line 2193 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 489 "parser.y" /* yacc.c:1646  */
    {
					printf("call.id \n");}
#line 2200 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 491 "parser.y" /* yacc.c:1646  */
    {
					printf("call [expression]\n");}
#line 2207 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 497 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = make_call((yyval.exprValue),(yyvsp[-1].exprValue));
					printf("call (elist)\n");}
#line 2214 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 500 "parser.y" /* yacc.c:1646  */
    {const char *  val;val=(yyvsp[0].exprValue)->sym->name;
			int i = scope;
			printf("lval name = %s\n",(yyvsp[0].exprValue)->sym->name);
			SymbolTableEntry * temp=NULL;
			if(lookUp(Table,val)==0 && (yyvsp[0].exprValue)->sym->type!=LIBFUNC){
				printf("%s undefined reference\n",val);
			}
			else{
				while(1){
					temp = lookUpScope(Table,val,USERFUNC,i);
					if(temp){
						if((temp->type==USERFUNC) || (temp->type==LIBFUNC)){ break;}
						else {temp=NULL;}
					}
					if(i==-1)break;
					i--;
				}
				if(temp && funcflag==0){printf("%s refers to function found in %d scope\n",val,i);}
				else{printf("%s undefined reference\n",val);}
			}	
	}
#line 2240 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 520 "parser.y" /* yacc.c:1646  */
    { if((yyvsp[0].callValue)->method == 1 && (yyvsp[0].callValue)->elist){
			expr* self = (yyvsp[-2].exprValue);
			puts("elist in callsufix exists");
			(yyvsp[-2].exprValue) = emit_iftableitem(member_item(self,(yyvsp[0].callValue)->name));//TODO : ADD FRONT
			(yyvsp[0].callValue)->elist->next = (expr*)malloc(sizeof(expr*));
			(yyvsp[0].callValue)->elist->next = self;
			}
			(yyval.exprValue) = make_call((yyvsp[-2].exprValue),(yyvsp[0].callValue)->elist);
	}
#line 2254 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 529 "parser.y" /* yacc.c:1646  */
    {
							expr* func;
							func = newexpr(programfunc_e);
							func->sym = (yyvsp[-4].exprValue)->sym;
							(yyvsp[-4].exprValue) = make_call(func,(yyvsp[-1].exprValue));
							


							printf("(function definition) (elist)\n");}
#line 2268 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 541 "parser.y" /* yacc.c:1646  */
    {(yyval.callValue)=(yyvsp[0].callValue);printf("normal call \n");}
#line 2274 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 542 "parser.y" /* yacc.c:1646  */
    {(yyval.callValue)=(yyvsp[0].callValue);printf("method call \n");}
#line 2280 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 546 "parser.y" /* yacc.c:1646  */
    {
					(yyval.callValue)->elist = (yyvsp[-1].exprValue);
					(yyval.callValue)->method = 0;
					(yyval.callValue)->name = "";
					printf("(elist) \n");}
#line 2290 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 554 "parser.y" /* yacc.c:1646  */
    {
		(yyval.callValue)->elist = (yyvsp[-1].exprValue);
		(yyval.callValue)->method = 1;
		(yyval.callValue)->name = (yyvsp[-3].stringValue);
		printf("..id (elist) \n");}
#line 2300 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 562 "parser.y" /* yacc.c:1646  */
    {		
					if(!(yyvsp[0].exprValue)){
						(yyval.exprValue) = (expr*)malloc(sizeof(expr));
						(yyval.exprValue)->sym = (struct symbol*)malloc(sizeof(struct symbol));
						(yyvsp[-1].exprValue)->next = NULL;
						(yyval.exprValue) = (yyvsp[-1].exprValue);
					}
					else{	 
						expr* tmp;
						tmp = (yyval.exprValue);
						while(tmp->next){
							tmp=tmp->next;
							
						}
						expr* temp2;
						temp2 = (yyvsp[0].exprValue);
						while(temp2->next){
							temp2=temp2->next;
							
						}
						temp2->next = (yyvsp[-1].exprValue);
						(yyvsp[-1].exprValue)->next = NULL;
						(yyval.exprValue) = reverse((yyvsp[0].exprValue));
						puts("ELIST1 DONE");
					}
					
				
			
					


				printf("expression \n");}
#line 2337 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 594 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = (expr*)malloc(sizeof(expr));(yyval.exprValue)=NULL;puts("EMPTY ELIST");}
#line 2343 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 598 "parser.y" /* yacc.c:1646  */
    {expr * temp=NULL;
					temp = (yyvsp[0].exprValue);
					
					if((yyvsp[-1].exprValue)->type == constnum_e || (yyvsp[-1].exprValue)->type==var_e){printf("             %f\n",(yyvsp[-1].exprValue)->numConst);}
					if(temp){
						while(temp->next){
							temp = temp->next;
						}
						temp->next = (yyvsp[-1].exprValue);
						(yyval.exprValue) = (yyvsp[0].exprValue);
					}
					else{
						(yyval.exprValue)=(yyvsp[-1].exprValue);
					}
					 	printf(",expression\n");}
#line 2363 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 613 "parser.y" /* yacc.c:1646  */
    {puts("EMPTY ELIST2");(yyval.exprValue)=NULL;}
#line 2369 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 615 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);}
#line 2375 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 616 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);}
#line 2381 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 621 "parser.y" /* yacc.c:1646  */
    {	expr* t;
					t = newexpr(newtable_e);
					t->sym = newtemp(Table);
					printf("table name = %s\n",t->sym->name);
					emit(tablecreate,t,NULL,NULL,-1,yylineno);
					int i =0;
					while((yyvsp[-1].exprValue)){
						emit(tablesetelem,t,NULL,(yyvsp[-1].exprValue),-1,yylineno);
						(yyvsp[-1].exprValue) = (yyvsp[-1].exprValue)->next;
					}
					(yyval.exprValue)=t;
}
#line 2398 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 634 "parser.y" /* yacc.c:1646  */
    {
					expr* t;
					t = newexpr(newtable_e);
					t->sym = newtemp(Table);					
					emit(tablecreate,NULL,NULL,t,-1,yylineno);
					expr* tempHead;
					tempHead = (yyvsp[-1].exprValue);
					tempHead = reverse(tempHead);
					while (tempHead){
						
						emit(tablesetelem,tempHead,tempHead->index,t,-1,yylineno);
						tempHead = tempHead->next;
					}
					(yyval.exprValue) = t;
		

					
}
#line 2421 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 655 "parser.y" /* yacc.c:1646  */
    {
					expr* tempHead;
					tempHead = (yyvsp[0].exprValue);
					if(tempHead){
						while(tempHead->next){
							tempHead = tempHead->next;
							
						}
						tempHead->next= (yyvsp[-1].exprValue);
						tempHead->next->next = NULL;
						(yyval.exprValue) = (yyvsp[0].exprValue);
					}
					else{
						(yyval.exprValue)=(yyvsp[-1].exprValue);
						(yyval.exprValue)->next = NULL;
					}
}
#line 2443 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 675 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue) = (expr*)malloc(sizeof(expr));
					expr* tempHead;
					tempHead = (yyvsp[0].exprValue);
					if(tempHead){
						while(tempHead->next){
							tempHead = tempHead->next;
						}
						tempHead->next = (yyvsp[-1].exprValue);
						tempHead->next->next=NULL;
						(yyval.exprValue)=(yyvsp[0].exprValue);
					}
					else{
						(yyval.exprValue)=(yyvsp[-1].exprValue);
						(yyval.exprValue)->next = NULL;
					}
}
#line 2465 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 692 "parser.y" /* yacc.c:1646  */
    {/*$$=(expr*)malloc(sizeof(expr));*/(yyval.exprValue)=NULL;}
#line 2471 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 696 "parser.y" /* yacc.c:1646  */
    {
					(yyval.exprValue)= newexpr(tableitem_e);
					(yyvsp[-3].exprValue)->index = (yyvsp[-1].exprValue);
					(yyval.exprValue) = (yyvsp[-3].exprValue);
					(yyval.exprValue)->next = NULL;

}
#line 2483 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 706 "parser.y" /* yacc.c:1646  */
    {scope++;}
#line 2489 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 706 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[-1].exprValue);hide(Table,scope);printf("{...}\n");scope--;}
#line 2495 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 710 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[-1].exprValue);(yyval.exprValue)->breaklist = merge((yyvsp[-1].exprValue)->breaklist,(yyvsp[0].exprValue)->breaklist);(yyval.exprValue)->conlist = merge((yyvsp[-1].exprValue)->conlist,(yyvsp[0].exprValue)->conlist);printf("{statement}\n");}
#line 2501 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 711 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)->breaklist = NULL;(yyval.exprValue)->conlist=NULL;printf("{}\n");}
#line 2507 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 716 "parser.y" /* yacc.c:1646  */
    {
			exitscopespace();
			(yyvsp[-2].symValue)->totallocals = (yyvsp[0].intValue);
			restorecurrscopeoffset(offsetPop(currscopeoffset()));
			(yyval.exprValue) = newexpr(programfunc_e);
			(yyval.exprValue)->sym = (yyvsp[-2].symValue);
			emit(funcend,NULL,NULL,lvalue_expr((yyvsp[-2].symValue)),-1,yylineno);
			funcflag--;
			if(funcInLoop==1)funcInLoop=0;
}
#line 2522 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 730 "parser.y" /* yacc.c:1646  */
    {funcflag++;}
#line 2528 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 730 "parser.y" /* yacc.c:1646  */
    {scope++;
		(yyval.symValue) = newSymbol((yyvsp[0].stringValue));
		(yyval.symValue)->type = programfunc_s;
		(yyval.symValue)->iaddress = nextquadlabel();
		emit(funcstart,NULL,NULL,lvalue_expr((yyval.symValue)),-1,yylineno);
		if(!isFull()){
			offsetPush(currscopeoffset());
		}
		enterscopespace();
		resetformalargsoffset();
		SymbolTableEntry * temp = NULL;
		temp = lookUpScope(Table,(yyvsp[0].stringValue),GLOBAL,scope-1);
		if(temp)
		temp->sym = (yyval.symValue);
}
#line 2548 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 746 "parser.y" /* yacc.c:1646  */
    {scope--;
					enterscopespace();
					resetfunctionlocalsoffset();	
				}
#line 2557 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 751 "parser.y" /* yacc.c:1646  */
    {	
			(yyval.intValue) = currscopeoffset();
			exitscopespace();
		
			}
#line 2567 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 768 "parser.y" /* yacc.c:1646  */
    {(yyval.stringValue)=(yyvsp[0].stringValue);const char* val = (yyvsp[0].stringValue);


				SymbolTableEntry * temp=NULL;
				temp = lookUpScope(Table,val,USERFUNC,scope);
				if(temp){
					if((temp->type == LOCALS)||(temp->type == FORMAL)||(temp->type == GLOBAL)){
						printf("REDEFINITION OF THIS NAME %s \n",temp->cat.varVal->value);
					}
					else{
						printf("%s() already exists in same scope\n",val);
					}
				}
				else{
					temp = lookUpScope(Table,val,USERFUNC,0);
					if(temp){
						if(temp->type == LIBFUNC){
							printf("error: %s function overrides library function\n",val);
						}
					}
					else{
						
						insert(Table,val,USERFUNC,yylineno,scope);
					}
				}
			}
#line 2598 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 794 "parser.y" /* yacc.c:1646  */
    {(yyval.stringValue) = funcNameGen();

			insert(Table,(yyval.stringValue),USERFUNC,yylineno,scope);


					}
#line 2609 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 803 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);}
#line 2615 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 804 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=newexpr_conststring((yyvsp[0].stringValue));printf("STRING \n");}
#line 2621 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 805 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=newexpr_constbool(-1);printf("NIL \n");}
#line 2627 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 806 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = newexpr_constbool(1);printf("TRUE \n");}
#line 2633 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 807 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = newexpr_constbool(0);printf("FALSE \n");}
#line 2639 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 811 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=newexpr_constnum((yyvsp[0].intValue));printf("INTEGER \n");}
#line 2645 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 812 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=newexpr_constnum((yyvsp[0].realValue));printf("REAL \n");}
#line 2651 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 816 "parser.y" /* yacc.c:1646  */
    {
						const char* val = (yyvsp[-1].stringValue);
			
						struct symbol* sym;						
						sym = newSymbol((yyvsp[-1].stringValue));
						sym->space = currscopespace();
						sym->offset = currscopeoffset();
						inccurrscopeoffset();
						(yyval.exprValue) = lvalue_expr(sym);
					if((yyvsp[0].exprValue)){
						expr* temp2;
						temp2 = (yyvsp[0].exprValue);
						while(temp2->next){
							temp2=temp2->next;
						}
						temp2->next = lvalue_expr(sym);
						(yyvsp[0].exprValue)->next->next = NULL;
						(yyval.exprValue) = reverse((yyvsp[0].exprValue));
					}
			insert(Table,val,FORMAL,yylineno,scope);
SymbolTableEntry *temp=NULL;			
temp = lookUpScope(Table,val,GLOBAL,scope);
temp->sym = sym;
			printf("new formal id with name %s\n",val);
			
		}
#line 2682 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 842 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=NULL;}
#line 2688 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 846 "parser.y" /* yacc.c:1646  */
    {const char* val = (yyvsp[-1].stringValue);
					expr * temp=NULL;
					temp = (yyvsp[0].exprValue);
					struct symbol* sym;						
					sym = newSymbol((yyvsp[-1].stringValue));
					sym->space = currscopespace();
					sym->offset = currscopeoffset();
					inccurrscopeoffset();
					(yyval.exprValue) = lvalue_expr(sym);

					if(temp){
						while(temp->next){
							temp = temp->next;
						}
						temp->next = lvalue_expr(sym);
						(yyvsp[0].exprValue)->next->next = NULL;
						(yyval.exprValue) = (yyvsp[0].exprValue);
					}
	    				insert(Table,val,FORMAL,yylineno,scope);
					SymbolTableEntry *temp2=NULL;			
					temp2 = lookUpScope(Table,val,GLOBAL,scope);
					temp2->sym = sym;
		    	}
#line 2716 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 869 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=NULL;}
#line 2722 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 874 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[-2].exprValue);
			(yyval.exprValue)=(expr*)malloc(sizeof(expr));
			
			if((yyvsp[-2].exprValue) && (yyvsp[-2].exprValue)->breaklist){
				if((yyvsp[0].exprValue)){puts("NAI");
					(yyval.exprValue)->breaklist=merge((yyvsp[-2].exprValue)->breaklist,(yyvsp[0].exprValue)->breaklist);}
				else
					(yyval.exprValue)->breaklist = (yyvsp[-2].exprValue)->breaklist;
			}
			else if((yyvsp[0].exprValue) && (yyvsp[0].exprValue)->breaklist){
				if((yyvsp[-2].exprValue))
					(yyval.exprValue)->breaklist = merge((yyvsp[0].exprValue)->breaklist,(yyvsp[-2].exprValue)->breaklist);
				else
					(yyval.exprValue)->breaklist = (yyvsp[0].exprValue)->breaklist;
			}
			else{
				(yyval.exprValue)->breaklist = NULL;
			}
			if((yyvsp[-2].exprValue) && (yyvsp[-2].exprValue)->conlist){
				if((yyvsp[0].exprValue))
					(yyval.exprValue)->conlist=merge((yyvsp[-2].exprValue)->conlist,(yyvsp[0].exprValue)->conlist);
				else
					(yyval.exprValue)->conlist = (yyvsp[-2].exprValue)->conlist;	
			}
			else if((yyvsp[0].exprValue) && (yyvsp[0].exprValue)->conlist){
				if((yyvsp[-2].exprValue))
					(yyval.exprValue)->conlist = merge((yyvsp[0].exprValue)->conlist,(yyvsp[-2].exprValue)->conlist);
				else
					(yyval.exprValue)->conlist = (yyvsp[0].exprValue)->conlist;
			}
			else{
				(yyval.exprValue)->conlist = NULL;
			}
			patchlabel((yyvsp[-3].intValue),(yyvsp[-1].intValue)+1);
			patchlabel((yyvsp[-1].intValue),nextquadlabel());
			}
#line 2763 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 910 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(yyvsp[0].exprValue);
				patchlabel((yyvsp[-1].intValue),nextquadlabel());}
#line 2770 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 915 "parser.y" /* yacc.c:1646  */
    {
		emit(if_eq,(yyvsp[-1].exprValue),newexpr_constbool('1'),NULL,nextquadlabel()+2,yylineno);
		(yyval.intValue) = nextquadlabel();
		emit(jump,NULL,NULL,NULL,-1,yylineno);
					}
#line 2780 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 928 "parser.y" /* yacc.c:1646  */
    {
					(yyval.intValue) = nextquadlabel();
					emit(jump,NULL,NULL,NULL,-1,yylineno);
		}
#line 2789 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 935 "parser.y" /* yacc.c:1646  */
    {emit(jump,NULL,NULL,NULL,(yyvsp[-3].intValue),yylineno);

					patchlabel((yyvsp[-2].intValue),nextquadlabel());

					struct list* temp = (yyvsp[-1].exprValue)->breaklist;
					while(temp){puts("BREAK awpignaoignaga");
						patchlabel(temp->label,nextquadlabel());
						temp = temp->next;
					}

					temp = (yyvsp[-1].exprValue)->conlist;
					/*while(temp){
						patchlabel(temp->label,$1);
						temp = temp->next;
					}*/


					(yyval.exprValue) = (expr*)malloc(sizeof(expr));




					/*if($3->breaklist){
					if(breakFlag!=0)
						patchlabel($3->breaklist->label,nextquadlabel());
					}
					if ($3->conlist){
					if(conFlag!=0)
						patchlabel($3->conlist->label,$1);
					}*/
					patchlabel((yyvsp[0].intValue),(yyvsp[-3].intValue));
					puts("while done");
				}
#line 2827 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 971 "parser.y" /* yacc.c:1646  */
    {
			(yyval.intValue) = nextquadlabel();
			}
#line 2835 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 977 "parser.y" /* yacc.c:1646  */
    {	
				 emit(if_eq,(yyvsp[-1].exprValue),newexpr_constbool('1'),NULL,nextquadlabel()+2,yylineno);
				 (yyval.intValue) = nextquadlabel();
				 emit(jump,NULL,NULL,NULL,-1,yylineno);	

				}
#line 2846 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 987 "parser.y" /* yacc.c:1646  */
    {}
#line 2852 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 987 "parser.y" /* yacc.c:1646  */
    {
	struct list* temp = (yyvsp[-1].exprValue)->breaklist;
	while(temp){
		patchlabel(temp->label,nextquadlabel());
		temp = temp->next;
	}
	temp = (yyvsp[-1].exprValue)->conlist;
	while(temp){
		patchlabel(temp->label,(yyvsp[-6].intValue)+1);
		temp = temp->next;
	}
	
	patchlabel((yyvsp[-7].forValue)->enter,(yyvsp[-3].intValue)+1);
	patchlabel((yyvsp[-6].intValue),nextquadlabel());
	patchlabel((yyvsp[-3].intValue),(yyvsp[-7].forValue)->test);
	patchlabel((yyvsp[0].intValue),(yyvsp[-6].intValue)+1);
}
#line 2874 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1005 "parser.y" /* yacc.c:1646  */
    {
		(yyval.forValue) =(struct forVal*)malloc(sizeof(struct forVal));
		(yyval.forValue)->test = (yyvsp[-2].intValue);
		(yyval.forValue)->enter = nextquadlabel();
		emit(if_eq,(yyvsp[-1].exprValue),newexpr_constbool('1'),NULL,0,yylineno);
}
#line 2885 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1012 "parser.y" /* yacc.c:1646  */
    {(yyval.intValue) = nextquadlabel();emit(jump,NULL,NULL,NULL,0,yylineno);}
#line 2891 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1014 "parser.y" /* yacc.c:1646  */
    {(yyval.intValue) = nextquadlabel();}
#line 2897 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1017 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue) = (expr*)malloc(sizeof(expr));(yyval.exprValue) = (yyvsp[-1].exprValue);if(funcflag>0)funcInLoop=1;}
#line 2903 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1018 "parser.y" /* yacc.c:1646  */
    {++loopcounter;}
#line 2909 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1019 "parser.y" /* yacc.c:1646  */
    {--loopcounter;}
#line 2915 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1021 "parser.y" /* yacc.c:1646  */
    {(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[-1].exprValue);printf("RETURN\n");if(funcflag==0){printf("Cannot use return while not in function ERROR\n");}}
#line 2921 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1024 "parser.y" /* yacc.c:1646  */
    {if(funcflag>0){(yyval.exprValue)=(expr*)malloc(sizeof(expr));(yyval.exprValue)=(yyvsp[0].exprValue);emit(ret,NULL,NULL,(yyvsp[0].exprValue),-1,yylineno);}else{printf("Cannot use return outside a function ERROR\n");}}
#line 2927 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1025 "parser.y" /* yacc.c:1646  */
    {if(funcflag>0){(yyval.exprValue)=(expr*)malloc(sizeof(expr));emit(ret,NULL,NULL,NULL,-1,yylineno);}else{printf("Cannot use return outside a function ERROR\n");}}
#line 2933 "parser.c" /* yacc.c:1646  */
    break;


#line 2937 "parser.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1028 "parser.y" /* yacc.c:1906  */
	
	
int yyerror (char* yaccProvidedMessage){
	fprintf(stderr, "%s: at line %d, before token: %s\n", yaccProvidedMessage, yylineno, yytext);
	fprintf(stderr, "INPUT NOT VALID\n");
}	
	
	
	
	
int main(int argc, char **argv)
{
	if(argc>1)
	{
		yyin=fopen(argv[1], "r");
		if(yyin==NULL)
		{
			fprintf(stderr, "Cannot open file.\n");
			return -1;
		}
	}
	else
	{
		yyin=stdin;
	}
		initFuncArray();
		Table = createTable();
		insert(Table,"print",LIBFUNC,0,0);
		insert(Table,"input",LIBFUNC,0,0);
		insert(Table,"objectmemberkeys",LIBFUNC,0,0);
		insert(Table,"objecttotalmembers",LIBFUNC,0,0);
		insert(Table,"objectcopy",LIBFUNC,0,0);
		insert(Table,"totalarguements",LIBFUNC,0,0);
		insert(Table,"arguement",LIBFUNC,0,0);
		insert(Table,"typeof",LIBFUNC,0,0);
		insert(Table,"strtonum",LIBFUNC,0,0);
		insert(Table,"sqrt",LIBFUNC,0,0);
		insert(Table,"cos",LIBFUNC,0,0);
		insert(Table,"sin",LIBFUNC,0,0);

		yyparse();
		
		

	 	 
	    printTabol(Table);
	if(nextquadlabel()){
	    //printQuads2();
	    printQuads();
	}
	generate();
	printTables();
	printInstructions();
	printTables_tofile();
	return 0;
}
