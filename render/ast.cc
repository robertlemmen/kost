#include "ast.h"

using namespace std;

FQN::FQN() {
}

FQN::FQN(const string &identifier, yy::location &loc) {
    // XXX
}

FQN::FQN(const FQN &parent, const string &identifier, yy::location &loc) {
    // XXX
}

ostream& operator<<(ostream& stream, const FQN& fqn) {
    // XXX
    return stream;
}

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

Value::Value(const FQN &fqn, yy::location &loc) {
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

