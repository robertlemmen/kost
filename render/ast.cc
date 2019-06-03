#include "ast.h"

using namespace std;

Value::Value() {
}

Value::Value(int intval, yy::location &loc) {
    // XXX
}

Value::Value(const string &value, yy::location &loc) {
    // XXX
}

Value::Value(const char *cstr, yy::location &loc) {
    // XXX
}

ostream& operator<<(ostream& stream, const Value& value) {
    // XXX
    return stream;
}

Property::Property() {
}

Property::Property(const string &key, const Value &value, yy::location &loc) {
    // XXX
}

ostream& operator<<(ostream& stream, const Property& value) {
    // XXX
    return stream;
}

