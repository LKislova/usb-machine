#include "DEF.h"

#include <iostream>
#include "stdlib.h"
#include "string.h"

line_t* new_line(variable* var) {
  line_t * vars = new line_t();
  return add_to_line(vars, var);
}

line_t* add_to_line(line_t * line, variable* var) {
  line->insert(*var);
  //std::cout << "add_to_line from  " << *var->first << '\n';
  return line;
}

lines_t*  new_lines(line_t* new_vars, line_t* current_vars) {
  lines_t* lines = new lines_t();
  return add_to_lines(new_vars, lines, current_vars);
}

lines_t* add_to_lines(line_t* new_vars, 
		      lines_t* old_vars, 
		      line_t* current_vars) {
  old_vars->push_back(new_vars);
  // for (line_t::iterator i = current_vars->begin(); 
  //      i != current_vars->end(); ++i) {
  //   std::cout << "add before  =" << i->first <<  ' ' << i->second << '\n';
  // }

  for(line_t::iterator i = new_vars->begin();  i != new_vars->end(); ++i){
    // std::cout << "current var =" << i->first <<  ' ' << i->second << '\n';
    current_vars->erase(i->first);
    current_vars->insert(*i);
  }
  // for (line_t::iterator i = current_vars->begin(); 
  //      i != current_vars->end(); ++i) {
  //   std::cout << "add after =" << i->first <<  ' ' << i->second << '\n';
  // }

  return old_vars;
}

double get_var(std::string v, line_t* current_vars) {
  for (line_t::iterator i = current_vars->begin(); i != current_vars->end(); ++i) {
    if (i->first.compare(v) == 0){
      return i->second;
    }
  }
  return 0.0;  
}

int yyerror(lines_t *l, line_t* current_vars, const char *msg) {
    // Add error handling routine as needed
  std::cout << msg << '\n';
  return 0;
}
