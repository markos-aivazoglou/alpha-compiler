/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 30 "parser.y" /* yacc.c:1909  */

	char* stringValue;
	int   intValue;
	double realValue;
	struct expr* exprValue;
	struct forVal* forValue;
	struct symbol* symValue;
	struct call* callValue;
	

#line 173 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
