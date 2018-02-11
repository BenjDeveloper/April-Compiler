%defines "parser.h"

%{
    #include <iostream>
    
    #include "include/assignment.hpp"
    #include "include/bioperator.hpp"
    #include "include/block.hpp"
    #include "include/double.hpp"
    #include "include/exprstatement.hpp"
    #include "include/identifier.hpp"
    #include "include/integer.hpp"
    #include "include/node.hpp"
    #include "include/methodcall.hpp"
    #include "include/string.hpp"
    #include "include/vardeclaration.hpp"

    using namespace april;
    
    extern int yylex();
    extern void yyerror(const char*);
    extern int line;
    extern int col;
    extern char* yytext;

    april::Block* programBlock;
%}

%union
{
    april::Node* node;
    april::Block* block;
    april::Statement* stmt;
    april::Identifier* ident;
    april::Expression* expr;
    april::VariableDeclaration* var_decl;
    std::string* string; 
    std::vector<april::Expression*> *exprvec;
    int token;
}

%token<string> TDIGIT TDOUBLE TIDENTIFIER 
%token<token> TPLUS TMIN TMUL TDIV TLET
%token<token> TCOLON TEQUAL TSC TJUMP TCOMMA
%token<token> TRBRACE TLBRACE
%token<token> TLPAREN TRPAREN TSTR

%type<ident> ident
%type<exprvec> call_args
%type<expr> expr binary_ope_expr basics
%type<stmt> stmt var_decl
%type<block> program stmts

%left TPLUS TMIN
%left TMUL TDIV

%start program

%%

program: %empty         { programBlock = new april::Block();}
    | stmts             { programBlock = $1; }
    ;

stmts: stmt             { $$ = new april::Block(); $$->statements.push_back($<stmt>1); }
    |  stmts stmt       { $1->statements.push_back($<stmt>2); }
    ;

stmt: var_decl          {  }
    | expr              { $$ = new april::ExpressionStatement(*$1); }
    ;

var_decl: TLET ident TCOLON ident TSC               { $$ = new april::VariableDeclaration(*$4, *$2);}
    | TLET ident TCOLON ident TEQUAL expr TSC       { $$ = new april::VariableDeclaration(*$4, *$2, $6); }
    ;

expr: binary_ope_expr                       { }
    | basics                                { $$ = $1; }
    | ident TLPAREN call_args TRPAREN TSC   { $$ = new april::MethodCall(*$1, *$3); }
    | ident                                 { $<ident>$ = $1; }                            
    ;

call_args: %empty               { $$ = new april::ExpressionList(); }
    | expr                      { $$ = new april::ExpressionList(); $$->push_back($1); }
    | call_args TCOMMA expr     { $$->push_back($3); }
    ;

binary_ope_expr: expr TPLUS expr        { $$ = new april::BinaryOperator(*$1, $2, *$3); } 
    | expr TMIN expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TMUL expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TDIV expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    ;

basics: TDIGIT                          { $$ = new april::Integer(std::atol($1->c_str())); delete $1; }
    |   TDOUBLE                         { $$ = new april::Double(std::atof($1->c_str())); delete $1; }
    |   TSTR                            { $$ = new april::String(yytext); }
    ;

ident: TIDENTIFIER                      { $$ = new april::Identifier(*$1); delete $1; }
%%

void yyerror(const char* msg)
{
    std::cout << "Error: " << msg << "\nLinea: " << line << "\nno esperaba " << yytext << std::endl;
    exit(1);
}