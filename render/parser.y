%skeleton "lalr1.cc"
%require "3.3"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>
#include <list>

#include "ast.h"

class driver;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.h"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  LPAREN  "("
  RPAREN  ")"
  LBRACKET  "["
  RBRACKET  "]"
  COMMA  ","
;

%token <std::string> SYMBOL "symbol"
%token <std::string> STRING "string literal"
%token <int> NUMBER "number"

%type <Value> value
%type <std::list<Value>> values
%type <Term> term
%type <std::list<Term>> terms
/* XXX perhaps these should be ast nodes to make it simpler, at least the array */
%type <TermContents> term_contents
%type <Array> array
%type <Array> array_contents

%printer { yyo << $$; } <*>;

%%
%start top_term;

top_term: term { drv.result = $1; }

term: SYMBOL LPAREN term_contents RPAREN { $$ = Term($1, $3, @$); }

term_contents: value     { $$ = TermContents($1, @$); }
    | array              { $$ = TermContents($1, @$); }
    | terms              { $$ = TermContents($1, @$); }

terms: term              { $$ = std::list<Term>();
                           $$.push_back($1); }
    | terms COMMA term   { $$ = std::list<Term>($1);
                           $$.push_back($3); }

values: value            { $$ = std::list<Value>();
                           $$.push_back($1); }
    | values COMMA value { $$ = std::list<Value>($1);
                           $$.push_back($3); }


value: STRING            { $$ = Value($1, @$); }
    | NUMBER             { $$ = Value($1, @$); }

array: LBRACKET array_contents RBRACKET { $$ = $2; }

array_contents: /* empty */ { $$ = Array(); }
    | values { $$ = Array($1, @$); }
    | terms  { $$ = Array($1, @$); }

%%

void yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
