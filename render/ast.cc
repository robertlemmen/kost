#include "ast.h"

using namespace std;

Value::Value() {
}

Value::Value(int intval) {
    // XXX
}

Value::Value(const string &value) {
    // XXX
}

Value::Value(const char *cstr) {
    // XXX
}

ostream& operator<<(ostream& stream, const Value& value) {
    // XXX
    return stream;
}

Property::Property() {
}

Property::Property(const string &key, const Value &value) {
    // XXX
}

ostream& operator<<(ostream& stream, const Property& value) {
    // XXX
    return stream;
}

