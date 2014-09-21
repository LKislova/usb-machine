#include "Parser.h"
#include <iostream>
#include "cstdio"
#include "DEF.h"

extern void yyrestart(FILE*);

int main() {
  lines_t *result = new lines_t();
  line_t *current_vars = new line_t();
  FILE * f = fopen("test_template.dat", "r");

  std::cout << "Hello, my master.\n";
  yyrestart(f);
  yyparse(result, current_vars);
  fclose(f);
  std::cout << "Closed\n";
  return 0;  
}
