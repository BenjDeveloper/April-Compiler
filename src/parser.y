%defines "parser.h"

%{
    #include <iostream>
    
    #include "include/assignment.hpp"
    #include "include/bioperator.hpp"
	#include "include/conditional.hpp"
	#include "include/comparasionope.hpp"
    #include "include/unaryope.hpp"
	#include "include/block.hpp"
    #include "include/double.hpp"
    #include "include/boolean.hpp"
    #include "include/exprstatement.hpp"
    #include "include/identifier.hpp"
    #include "include/integer.hpp"
    #include "include/node.hpp"
    #include "include/methodcall.hpp"
    #include "include/string.hpp"
    #include "include/vardeclaration.hpp"
    #include "include/vardeclarationdeduce.hpp"
	#include "include/scope.hpp"
    #include "include/forloop.hpp"

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

%token<string> TDIGIT TDOUBLE TIDENTIFIER TBOOLEAN 
%token<token> TPLUS TMIN TMUL TDIV TVAR
%token<token> TCOLON TEQUAL TSC TJUMP TCOMMA TCOEQU
%token<token> TRBRACE TLBRACE
%token<token> TLPAREN TRPAREN TSTR
%token<token> TCOMNE TCOMEQ TCOMLE TCOMGE TCOMLT TCOMGT
%token<token> TAND TOR TNOT
%token<token> TIF TELSE TFOR

%type<ident> ident
%type<exprvec> call_args
%type<expr> expr binary_ope_expr basics boolean_expr unary_ope
%type<stmt> stmt var_decl conditional scope for
%type<block> program stmts block
%type<token> comparasion

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
    | expr              { $$ = new april::ExpressionStatement($1); }
    | conditional
	| scope
	| for
    ;

for: TFOR expr block    { $$ = new april::ForLoop($2, $3); }

scope: block			{ $$ = new april::Scope($1); }
	;

conditional: TIF expr block					{ $$ = new april::Conditional($2, *$3); }
	| TIF expr block TELSE block			{ $$ = new april::Conditional($2,* $3, *$5); }
	;

block: TLBRACE stmts TRBRACE				{ $$ = $2; }
	 | TLBRACE TRBRACE						{ $$ = new april::Block();  }
	 ;

var_decl: TVAR ident TCOLON ident TSC               { $$ = new april::VariableDeclaration(*$4, *$2);}
    | TVAR ident TCOLON ident TEQUAL expr TSC       { $$ = new april::VariableDeclaration(*$4, *$2, $6); }
    | ident TCOEQU expr TSC                         { $$ = new april::VariableDeclarationDeduce(*$1, $3); }
    ;

expr: binary_ope_expr                       { }
    | ident TEQUAL expr TSC                 { $$ = new april::Assignment(*$<ident>1, *$3); }
    | basics                                { $$ = $1; }
    | ident TLPAREN call_args TRPAREN TSC   { $$ = new april::MethodCall(*$1, *$3); }
    | ident                                 { $<ident>$ = $1; }                            
    | boolean_expr
	| unary_ope
	;

unary_ope: TNOT expr 			{ $$ = new april::UnaryOpe($1, *$2); }

call_args: %empty               { $$ = new april::ExpressionList(); }
    | expr                      { $$ = new april::ExpressionList(); $$->push_back($1); }
    | call_args TCOMMA expr     { $$->push_back($3); }
    ;

binary_ope_expr: expr TPLUS expr        { $$ = new april::BinaryOperator(*$1, $2, *$3); } 
    | expr TMIN expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TMUL expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TDIV expr                    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
	| expr TAND expr					{ $$ = new april::BinaryOperator(*$1, $2, *$3); }
	| expr TOR expr						{ $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | TLPAREN expr TRPAREN              { $$ = $2; }
    ;


boolean_expr: expr comparasion expr		{ $$ = new april::ComparasionOpe(*$1, $2, *$3);} 
	;

comparasion: TCOMNE | TCOMEQ | TCOMLE | TCOMGE | TCOMLT | TCOMGT
	;

basics: TDIGIT                          { $$ = new april::Integer(std::atol($1->c_str())); delete $1; }
    |   TDOUBLE                         { $$ = new april::Double(std::atof($1->c_str())); delete $1; }
    |   TSTR                            { $$ = new april::String(yytext); }
    |   TBOOLEAN                        { $$ = new april::Boolean(*$1); delete $1; }
    ;

ident: TIDENTIFIER                      { $$ = new april::Identifier(*$1); delete $1; }
%%

void yyerror(const char* msg)
{
    std::cout << "Error: " << msg << "\nLinea: " << line << "\nno esperaba " << yytext << std::endl;
    exit(1);
}
