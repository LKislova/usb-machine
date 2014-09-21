/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
/* Line 2053 of yacc.c  */
#line 1 "grammar.yy"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  
#include "DEF.h"
#include "math.h"
#include "ast.h"
#include "stdio.h"
#include <iostream>
extern "C" int yylex(void);

#endif


/* Line 2053 of yacc.c  */
#line 61 "Parser.h"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARS = 258,
     NUMBER = 259,
     INTEGER = 260,
     EOL = 261,
     END = 262,
     OP = 263,
     CP = 264,
     EQU = 265,
     Error_exit = 266,
     SPLITTER = 267,
     Error = 268,
     PLUS = 269,
     MINUS = 270,
     MULT = 271,
     DIVI = 272,
     COMMA = 273,
     SIN = 274,
     COS = 275,
     TAN = 276,
     ASIN = 277,
     ACOS = 278,
     ATAN = 279,
     SINH = 280,
     COSH = 281,
     TANH = 282,
     ASINH = 283,
     ACOSH = 284,
     ATANH = 285,
     EXP = 286,
     LOG = 287,
     LOG10 = 288,
     SQRT = 289,
     FABS = 290,
     POW = 291
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 22 "grammar.yy"

  variable* var;
  std::string* key;
  
  AST* ast;
  ast_variable_t* ast_variable;
  ast_line_t* ast_line;
  ast_lines_t* ast_lines;

  double value;
  int i;
  line_t* line;
  lines_t* lines;


/* Line 2053 of yacc.c  */
#line 128 "Parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (lines_t *result, line_t *current_vars);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */
