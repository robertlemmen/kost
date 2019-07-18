#ifndef AST_H
#define AST_H

#include <ostream>
#include <list>
#include <variant>

#include "location.hh"

class Term;

class Value {
    public:
        Value();
        Value(int intval, yy::location &loc);
        Value(const std::string &value, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const Value& value);

    private:
        std::variant<int, std::string> contents_; 
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Value& value);

class Array {
    public:
        Array(); // XXX we should have case with loc for empty arrrays
        Array(const std::list<Value> &values, yy::location &loc);
        Array(const std::list<Term> &terms, yy::location &loc);

        friend std::ostream& operator<<(std::ostream& stream, const Array &array);
    private:
        std::variant<std::list<Value>,std::list<Term>> contents_;
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Array &array);

class TermContents {
    public:
        TermContents();
        TermContents(const Value &value, yy::location &loc);
        TermContents(const Array &array, yy::location &loc);
        TermContents(const std::list<Term> &terms, yy::location &loc);
   
        friend std::ostream& operator<<(std::ostream& stream, const TermContents& contents);
    private:
        std::variant<Value,Array,std::list<Term>> contents_; 
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const TermContents &contents);

class Term {
    public:
        Term();
        Term(const std::string &name, const TermContents &contents, yy::location &loc);
   
        friend std::ostream& operator<<(std::ostream& stream, const Term& term);
    private:
        std::string name_;
        TermContents contents_;
        yy::location loc_;
};

std::ostream& operator<<(std::ostream& stream, const Term &term);

std::ostream& operator<<(std::ostream& stream, const std::list<Term> &terms);
std::ostream& operator<<(std::ostream& stream, const std::list<Value> &values);

#endif /* AST_H */
