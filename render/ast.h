#ifndef AST_H
#define AST_H

#include <ostream>

#include "location.hh"

class FQN {
    public:
        FQN();
        FQN(const std::string &identifier, yy::location &loc);
        FQN(const FQN &parent, const std::string &identifier, yy::location &loc);
};

std::ostream& operator<<(std::ostream& stream, const FQN& fqn);

class Value {
    public:
        Value();
        Value(int intval, yy::location &loc);
        Value(const std::string &value, yy::location &loc);
        Value(const char *cstr, yy::location &loc);
        Value(const FQN &fqn, yy::location &loc);
};

std::ostream& operator<<(std::ostream& stream, const Value& value);

class Property {
    public:
        Property();
        Property(const std::string &key, const Value &value, yy::location &loc);
};

std::ostream& operator<<(std::ostream& stream, const Property& property);

#endif /* AST_H */
