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
  COLON  ":"
  DCOLON  "::"
  LBRACKET  "{"
  RBRACKET  "}"
;

%token <std::string> IDENTIFIER "identifier"
%token <std::string> STRING "string literal"
%token <int> NUMBER "number"

%type <std::string> type
%type <Property> property
%type <Value> value
%type <FQN> fqn
%type <std::list<Property>> properties
%type <Entity> entity
%type <std::list<Entity>> entities
%type <std::pair<std::list<Property>,std::list<Entity>>> body

%printer { yyo << $$; } <*>;

%%
%start opt_entities;

opt_entities: /* empty */                       { drv.result = std::list<Entity>(); }
    | entities                                  { drv.result = $1; }

entities: entity                                { $$ = std::list<Entity>();
                                                  $$.push_back($1); }
    | entities entity                           { $$ = std::list<Entity>($1);
                                                  $$.push_back($2); }

entity: type IDENTIFIER body                    { $$ = Entity($1, $2, $3.first, $3.second, @$); }
    | type body                                 { $$ = Entity($1, std::string(""), $2.first, $2.second, @$); }

type: IDENTIFIER                                { $$ = $1; }

body: LBRACKET properties entities RBRACKET     { $$ = std::make_pair($2, $3); }
    | LBRACKET properties RBRACKET              { $$ = std::make_pair($2, std::list<Entity>()); } 
    | LBRACKET entities RBRACKET                { $$ = std::make_pair(std::list<Property>(), $2); }
    | LBRACKET RBRACKET                         { $$ = std::make_pair(std::list<Property>(), std::list<Entity>()); }

properties: property                            { $$ = std::list<Property>(); 
                                                  $$.push_back($1); }
    | properties property                       { $$ = std::list<Property>($1);
                                                  $$.push_back($2); }

property: IDENTIFIER COLON value                { $$ = Property($1, $3, @$); }

fqn: IDENTIFIER                                 { $$ = FQN($1, @$); }
    | fqn DCOLON IDENTIFIER                     { $$ = FQN($1, $3, @$); }

value: NUMBER                                   { $$ = Value($1, @$); }
    | STRING                                    { $$ = Value($1, @$); }
    | fqn                                       { $$ = Value($1, @$); }

%%

void yy::parser::error(const location_type& l, const std::string& m) {
    std::cerr << l << ": " << m << '\n';
}
