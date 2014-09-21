%code requires {
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  
#include "DEF.h"
#include "math.h"
#include "ast.h"
#include "stdio.h"
#include <iostream>
extern "C" int yylex(void);

#endif
}

%output  "Parser.cpp"
%defines "Parser.h"
 
%parse-param { lines_t *result }
%parse-param { line_t *current_vars }

%union 
{
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
}

%token <key> VARS
%token <value> NUMBER
%token <i> INTEGER

%token EOL
%token END
%token OP CP
%token EQU
%token Error_exit
%token SPLITTER
%token Error

%token PLUS
%token MINUS
%token MULT
%token DIVI
%token COMMA

%token SIN
%token COS
%token TAN
%token ASIN
%token ACOS
%token ATAN

%token SINH
%token COSH
%token TANH
%token ASINH
%token ACOSH
%token ATANH

%token EXP
%token LOG
%token LOG10
%token SQRT
%token FABS
%token POW

%type <lines> code_exp 
%type <line> line
%type <var> exp
%type <ast> term factor IB_exp
%type <ast_variable> ast_exp
%type <ast_line> ast_line
%type <ast_lines> ast_lines
%type <lines> loop

%%
input:
| code_exp END {
  return 0;
 } 
;

code_exp: code_exp EOL line { 
  $$ = add_to_lines($3, result, current_vars);
 }
| code_exp EOL loop
| code_exp EOL
| line { 
  $$ = add_to_lines($1, result, current_vars);
 }
| loop
;

loop: MULT INTEGER EOL ast_lines  MULT{

  for (int i = 0; i < $2; ++i) {
    for (ast_lines_t::iterator lines_i = $4->begin();
	 lines_i != $4->end(); ++lines_i) {
      line_t * line = new line_t();
      for (ast_line_t::iterator line_i = (*lines_i)->begin(); 
	   line_i != (*lines_i)->end(); ++line_i) {
	variable var(line_i->first, eval(line_i->second, current_vars));
	line->insert(var);
      }
      add_to_lines(line, result, current_vars);
      // for (line_t::iterator i = current_vars->begin(); 
      // 	   i != current_vars->end(); ++i) {
      // 	std::cout << "current var =" << i->first <<  ' ' << i->second << '\n';
      // }
    }
  }
  $$ = NULL;
 }
;

ast_lines: ast_lines ast_line EOL {
  $$ = add_to_ast_lines($2, $1);
 }
| ast_line EOL {
  $$ = new_ast_lines($1);
  }
;

ast_line: ast_line SPLITTER ast_exp {
  $$ = add_to_ast_line($1, $3);
 }
| ast_exp {
  $$ = new_ast_line($1);
  }
;

ast_exp: VARS EQU IB_exp {
  $$ = new ast_variable_t(*$1, $3);
};

line: line SPLITTER exp { 
      $$ = add_to_line($1, $3);
   }
  | exp {
      $$ = new_line($1);
    }
  ;

exp: VARS EQU IB_exp {
  $$ = new variable(*$1, eval($3, current_vars));
  }
  ;

IB_exp: IB_exp PLUS factor { $$ = new AST($1, $3, PLUS); }
  | IB_exp MINUS factor { $$ = new AST($1, $3, MINUS); }
  | factor
  ;

factor: factor MULT term {  $$ = new AST($1, $3, MULT); }
  | factor DIVI term {  $$ = new AST($1, $3, DIVI); }
  | term
  ;

term: VARS { 
  $$ = new AST(*($1)); }
  | NUMBER { $$ = new AST($1); }
  | INTEGER { $$ = new AST((double) $1); }
  | MINUS term { $$ = new AST(new AST(0.0), $2, MINUS); }
  | OP IB_exp CP { $$ = $2; }
  | SIN OP IB_exp CP { $$ = new AST($3, SIN); }
  | COS OP IB_exp CP { $$ = new AST($3, COS); }
  | TAN OP IB_exp CP { $$ = new AST($3, TAN); }
  | ASIN OP IB_exp CP { $$ = new AST($3, ASIN); }
  | ACOS OP IB_exp CP { $$ = new AST($3, ACOS); }
  | ATAN OP IB_exp CP { $$ = new AST($3, ATAN); }
  | SINH OP IB_exp CP { $$ = new AST($3, SINH); }
  | COSH OP IB_exp CP { $$ = new AST($3, COSH); }
  | TANH OP IB_exp CP { $$ = new AST($3, TANH); }
  | ASINH OP IB_exp CP { $$ = new AST($3, ASINH); }
  | ACOSH OP IB_exp CP { $$ = new AST($3, ACOSH); }
  | ATANH OP IB_exp CP { $$ = new AST($3, ATANH); }
  | EXP OP IB_exp CP { $$ = new AST($3, EXP); }
  | LOG OP IB_exp CP { $$ = new AST($3, LOG); }
  | LOG10 OP IB_exp CP { $$ = new AST($3, LOG10); }
  | SQRT OP IB_exp CP { $$ = new AST($3, SQRT); }
  | FABS OP IB_exp CP { $$ = new AST($3, FABS); }
  | POW OP IB_exp COMMA IB_exp CP { $$ = new AST($3, $5, POW); }
  ;
%%
