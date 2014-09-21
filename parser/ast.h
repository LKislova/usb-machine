#ifndef AST_H
#define AST_H

#include "parsertypes.h"

enum AST_t{
  var = 1,
  num = 2,
  com = 4
};

class AST {
  
public:
  AST(double d);
  AST(std::string s);
  AST(AST* left, AST* right, int mOperation);
  AST(AST* ast, int mOperation);
  AST* mLeft;
  AST* mRight;
  double mValue;
  std::string mKey;
  int mOperation;
  enum AST_t mType;
};
  
double eval(AST *ast, line_t* current_line);

typedef std::pair< std::string, AST* > ast_variable_t;
typedef std::map< std::string, AST* > ast_line_t;
typedef std::list< std::map< std::string, AST* > * > ast_lines_t;

ast_line_t* new_ast_line(ast_variable_t* var);
ast_line_t* add_to_ast_line(ast_line_t * line, ast_variable_t* var);
ast_lines_t* new_ast_lines(ast_line_t* new_vars);
ast_lines_t* add_to_ast_lines(ast_line_t* new_vars, 
			      ast_lines_t* old_vars);
#endif //AST_H
