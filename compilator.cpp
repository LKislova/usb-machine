#include "compilator.h"

extern FILE* yyin;
extern void yyrestart(FILE*);

Compilator::Compilator(const char* filename) {
    inputFile = fopen(filename, "r");

}

void Compilator::compile() {
    if (inputFile == NULL){
        return;
    }

    compiledLines = new std::list< std::map< std::string, double > * >;
    errors = new std::string();
    line_t current_vars;
    yyrestart(inputFile);
    yyparse(compiledLines, &current_vars);
    printf("\n%d    %d\n", compiledLines->size(), current_vars.size());
    fclose(inputFile);
}

double safullyGetCoor(line_t *line, std::string coor, double *def) {
    double c = *def;
    line_t::iterator point_x = line->find(coor);
    if (point_x != line->end()) {
        c = point_x->second;
        *def = c;
    }
    return c;
}

lines_t* Compilator::getLines() {
    if (compiledLines == NULL) {
        return new lines_t();
    }
    double x = 0.0, y = 0.0, z = 0.0, f = 0.0, s = 0.0, p = 0.0;
    std::string key_x("x"), key_y("y"), key_z("z"), key_f("f"), key_s("s"),
            key_p("p");
    foreach(line_t *line, *compiledLines) {
        line->insert(variable(key_x, safullyGetCoor(line, key_x, &x)));
        line->insert(variable(key_y, safullyGetCoor(line, key_y, &y)));
        line->insert(variable(key_z, safullyGetCoor(line, key_z, &z)));
        line->insert(variable(key_f, safullyGetCoor(line, key_f, &f)));
        line->insert(variable(key_s, safullyGetCoor(line, key_s, &s)));
        line->insert(variable(key_p, safullyGetCoor(line, key_p, &p)));
    }

    return compiledLines;
}

std::string* Compilator::getErrors() {
    return errors;
}
