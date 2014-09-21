#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include <list>
#include "parsertypes.h"


#define INVALID_VAR 111111

double get_var(std::string v, line_t* current_vars);

variable* new_var(std::string* v, double n);

line_t* new_line(variable* var);
line_t* add_to_line(line_t* vars, variable* var);

lines_t* new_lines(line_t* new_vars, 
		   line_t* current_vars);
lines_t* add_to_lines(line_t* new_vars, 
		      lines_t* old_vars, 
		      line_t* current_vars);

int yyerror(lines_t *l, line_t* current_vars, const char *msg);
#endif // PARSER_H
