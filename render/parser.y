%skeleton "lalr1.cc"
%require "3.3"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string>

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
  COLON  ":"
  DCOLON  "::"
  LBRACKET  "{"
  RBRACKET  "}"
;

%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string literal"
%token <int> NUMBER "number"

%printer { yyo << $$; } <*>;

%%
%start opt_entities;

opt_entities: /* empty */
    | entities;

entities: entity
    | entities entity;

entity: type identifier body
    | type body;

type: identifier;

body: LBRACKET properties entities RBRACKET  
    | LBRACKET properties RBRACKET  
    | LBRACKET entities RBRACKET  
    | LBRACKET RBRACKET;

properties: property
    | properties property;

property: IDENTIFIER COLON value 

identifier: IDENTIFIER;

fqn: IDENTIFIER
    | fqn DCOLON IDENTIFIER;

value: NUMBER
    | STRING
    | fqn;

%%

void yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
