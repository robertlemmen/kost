#ifndef AST_H
#define AST_H

#include <ostream>

class Value {
    public:
        Value();
        Value(int intval);
        Value(const std::string &value);
        Value(const char *cstr);
};

std::ostream& operator<<(std::ostream& stream, const Value& value);

class Property {
    public:
        Property();
        Property(const std::string &key, const Value &value);
};

std::ostream& operator<<(std::ostream& stream, const Property& property);

#endif /* AST_H */
