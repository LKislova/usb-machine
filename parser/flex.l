/* yylineno -- it store line number */
%{
#include "DEF.h"
#include "Parser.h"
#include <string>
%}

 
%option warn nodefault
 
%option noyywrap never-interactive nounistd
%option yylineno

%%
[ \t]*"="[ \t]* {
  return EQU;
}


[0-9]+ {
  yylval.i = atoi(yytext);
  return INTEGER;
}

[0-9]+"."([0-9]*)?([Ee][+-]?[0-9]+)? |
"."[0-9]*([Ee][+-]?[0-9]+)? { 
  yylval.value = atof(yytext);
  //printf("catch num = \"%e\"\n", yylval.value);
  return NUMBER;
}

(pi) {
  yylval.value = 3.1415926535897932384626433832795;
  return NUMBER;
}

(e) {
  yylval.value = exp(1);
  return NUMBER;
}

[ \t]*"+"[ \t]*  {
  return PLUS; 
}

[ \t]*"-"[ \t]*  {
  return MINUS; 
}

[ \t]*"*"[ \t]*  {
  return MULT; 
}

[ \t]*"/"[ \t]*  {
  return DIVI; 
}

[ \t]*","[ \t]*  {
  return COMMA; 
}

"("[ \t]*  {
  return OP; 
}

[ \t]*")"  {
  return CP; 
}

(sin) {
  return SIN;
}

(cos) {
  return COS;
}

(tan) {
  return TAN;
}

(asin) {
  return ASIN;
}

(acos) {
  return ACOS;
}

(atan) {
  return ATAN;
}

(sinh) {
  return SINH;
}

(cosh) {
  return COSH;
}

(tanh) {
  return TANH;
}

(asinh) {
  return ASINH;
}

(acosh) {
  return ACOSH;
}

(atanh) {
  return ATANH;
}

(exp) {
  return EXP;
}

(log) {
  return LOG;
}

(log10) {
  return LOG10;
}

(sqrt) {
  return SQRT;
}

(fabs) {
  return FABS;
}

(pow) {
  return POW;
}

([a-zA-Z][a-zA-Z0-9]*) {
  yylval.key = new std::string(yytext);
  return VARS;
}

 ([ \t]*\r\n|[ \t]*\n)+ {
  return EOL; 
}

[ \t]+ {
  return SPLITTER;
}

<<EOF>> {
  return END;
}

. {
  printf("unhandled: %s\n", yytext);
  return Error_exit;
}

