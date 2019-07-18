#include "ast.h"

using namespace std;

Value::Value() {
}

Value::Value(int intval, yy::location &loc):
        contents_(intval),
        loc_(loc) {
}

Value::Value(const string &value, yy::location &loc):
        contents_(value),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const Value &value) {
    visit([&stream](auto const& e){ stream << e; }, value.contents_);
    return stream;
}

Term::Term() {
}

Term::Term(const string &name, const TermContents &contents, yy::location &loc):
        name_(name),
        contents_(contents),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const Term &term) {
    stream << term.name_ << "(" << term.contents_ << ")";
    return stream;
}

TermContents::TermContents() {
}

TermContents::TermContents(const Value &value, yy::location &loc):
        contents_(value),
        loc_(loc) {
}

TermContents::TermContents(const Array &array, yy::location &loc):
        contents_(array),
        loc_(loc) {
}

TermContents::TermContents(const list<Term> &terms, yy::location &loc):
        contents_(terms),
        loc_(loc) {
}

ostream& operator<<(ostream &stream, const TermContents &contents) {
    visit([&stream](auto const& e){ stream << e; }, contents.contents_);
    return stream;
}

Array::Array() {
}

Array::Array(const list<Value> &values, yy::location &loc):
        contents_(values),
        loc_(loc) {
}

Array::Array(const list<Term> &terms, yy::location &loc):
        contents_(terms),
        loc_(loc) {
}

ostream& operator<<(ostream& stream, const Array &array) {
    stream << "[";
    visit([&stream](auto const& e){ stream << e; }, array.contents_);
    stream << "]";
    return stream;
}

ostream& operator<<(ostream &stream, const list<Term> &terms) {
    bool first = true;
    for (auto &term : terms) {
        if (!first) {
            stream << ", ";
        }
        stream << term;
        first = false;
    }
    return stream;
}

ostream& operator<<(ostream& stream, const list<Value> &values) {
    bool first = true;
    for (auto &value : values) {
        if (!first) {
            stream << ", ";
        }
        stream << value;
        first = false;
    }
    return stream;
}
