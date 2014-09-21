#include "ast.h"
#include "Parser.h"
#include <iostream>

AST::AST(double d) {
  this->mLeft = NULL;
  this->mRight = NULL;
  this->mType = num;
  this->mValue = d;
}

AST::AST(std::string s) {
  this->mLeft = NULL;
  this->mRight = NULL;
  this->mType = var;
  this->mValue = 0.0;
  this->mKey = s;
}

AST::AST(AST* left, AST* right, int operation) {
  this->mLeft = left;
  this->mRight = right;
  this->mType = com;
  this->mValue = 0.0;
  this->mOperation = operation;
}

AST::AST(AST* ast, int operation) {
  this->mLeft = ast;
  this->mRight = NULL;
  this->mType = com;
  this->mValue = 0.0;
  this->mOperation = operation;
}

double eval(AST *ast, line_t* current_line){
  switch(ast->mType){
  case var:
    return get_var(ast->mKey, current_line);
  case num:
    return ast->mValue;
  case com:
    switch(ast->mOperation) {
    case PLUS:
      return eval(ast->mLeft, current_line) + eval(ast->mRight, current_line);
    case MINUS:
      return eval(ast->mLeft, current_line) - eval(ast->mRight, current_line);
    case MULT:
      return eval(ast->mLeft, current_line) * eval(ast->mRight, current_line);
    case DIVI:
      return eval(ast->mLeft, current_line) / eval(ast->mRight, current_line);
    case SIN:
      return sin(eval(ast->mLeft, current_line));
    case COS:
      return cos(eval(ast->mLeft, current_line));
    case TAN:
      return tan(eval(ast->mLeft, current_line));

    case ASIN:
      return asin(eval(ast->mLeft, current_line));
    case ACOS:
      return acos(eval(ast->mLeft, current_line));
    case ATAN:
      return atan(eval(ast->mLeft, current_line));

    case SINH:
      return sinh(eval(ast->mLeft, current_line));
    case COSH:
      return cosh(eval(ast->mLeft, current_line));
    case TANH:
      return tanh(eval(ast->mLeft, current_line));

    case ASINH:
      return asinh(eval(ast->mLeft, current_line));
    case ACOSH:
      return acosh(eval(ast->mLeft, current_line));
    case ATANH:
      return atanh(eval(ast->mLeft, current_line));

    case EXP:
      return exp(eval(ast->mLeft, current_line));
    case LOG:
      return log(eval(ast->mLeft, current_line));
    case LOG10:
      return log10(eval(ast->mLeft, current_line));
    case SQRT:
      return sqrt(eval(ast->mLeft, current_line));
    case FABS:
      return fabs(eval(ast->mLeft, current_line));
    case POW:
      return pow(eval(ast->mLeft, current_line), eval(ast->mRight, current_line));
    }
  }
}

ast_line_t* new_ast_line(ast_variable_t* var) {
  ast_line_t * line = new ast_line_t();
  return add_to_ast_line(line, var);
}

ast_line_t* add_to_ast_line(ast_line_t * line, ast_variable_t* var) {
  line->insert(*var);
  return line;
}

ast_lines_t*  new_ast_lines(ast_line_t* new_vars) {
  ast_lines_t* lines = new ast_lines_t();
  return add_to_ast_lines(new_vars, lines);
}

ast_lines_t* add_to_ast_lines(ast_line_t* new_vars, 
			      ast_lines_t* old_vars) {
  old_vars->push_back(new_vars);
  return old_vars;
}

