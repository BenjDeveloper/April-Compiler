%defines "parser.h"

%{

#include <iostream>

extern void yyerror(const char*);
extern int yylex();

%}

%union
{ 
    int _INT;
    float _FLOAT;
}

%token<_INT> INT
%token<_FLOAT> FLOAT
%token<_INT> TOK
%type<_FLOAT> expr

%left '+' '-'
%left '*' '/'
%right TOK
%%

program: %empty
    | program line
    | program error '\n'
    ;

line: '\n'
    | expr line { std::cout <<"Value: "<< $1 << std::endl; }
    ;

expr: FLOAT                 { $$ = $1; }
    | INT                   { $$ = $1; }
    | expr '+' expr         { $$ = $1 + $3; }
    | expr '-' expr         { $$ = $1 - $3; }
    | expr '*' expr         { $$ = $1 * $3; }
    | expr '/' expr         { $$ = $1 / $3; }
    | '-' expr %prec TOK    { $$ = -1*$2; }
    | '(' expr ')'          { $$ = $2; }
    ;

%%