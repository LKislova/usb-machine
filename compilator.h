#ifndef COMPILATOR_H
#define COMPILATOR_H

#include "parsertypes.h"
#include "DEF.h"
#include "Parser.h"
#include <string>
#include <cstdio>
#include <QObject>

class Compilator {

public:
    Compilator(const char* filename);
    void compile();
    lines_t* getLines();
    std::string* getErrors();

private:
    FILE* inputFile;
    lines_t* compiledLines = NULL;
    std::string* errors;
};

#endif // COMPILATOR_H
