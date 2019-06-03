#ifndef AST_H
#define AST_H

#include <ostream>

#include "location.hh"

class Value {
    public:
        Value();
        Value(int intval, yy::location &loc);
        Value(const std::string &value, yy::location &loc);
        Value(const char *cstr, yy::location &loc);
};

std::ostream& operator<<(std::ostream& stream, const Value& value);

class Property {
    public:
        Property();
        Property(const std::string &key, const Value &value, yy::location &loc);
};

std::ostream& operator<<(std::ostream& stream, const Property& property);

#endif /* AST_H */
