#ifndef PARSERTYPES_H
#define PARSERTYPES_H
#include <list>
#include <map>
#include <string>

typedef std::map< std::string, double > line_t;
typedef std::list< std::map< std::string, double > * > lines_t;
typedef std::pair< std::string, double > variable;

#endif // TYPEDEFS_H
