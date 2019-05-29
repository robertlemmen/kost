%skeleton "lalr1.cc"
%require "3.3"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
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
  ASSIGN  ":="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"
%type  <int> exp

%printer { yyo << $$; } <*>;

%%
%start entities;

entities: /* empty */
    | entities entity;

entity: type identifier body
    | type body;

type: identifier;

body: '{' properties entities '}'

properties: /* empty */
    | properties property;

property: identifier ':' value;

identifier: IDENTIFIER;

object: exp {};

value: NUMBER;

%left "+" "-";
%left "*" "/";
exp:
  "number"
| exp "+" exp   { $$ = $1 + $3; }
| exp "-" exp   { $$ = $1 - $3; }
| exp "*" exp   { $$ = $1 * $3; }
| exp "/" exp   { $$ = $1 / $3; }
| "(" exp ")"   { $$ = $2; }
%%

void yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
