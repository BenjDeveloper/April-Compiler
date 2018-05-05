%defines "parser.h"

%{
    #include <iostream>
    #include "headers/symbol.hpp"
    #include "headers/node.hpp"
    #include "headers/statement.hpp"
    #include "headers/expression.hpp"
    #include "headers/exprstatement.hpp"
    #include "headers/block.hpp"
    #include "headers/codegencontext.hpp"
    #include "headers/integer.hpp"
    #include "headers/double.hpp"
    #include "headers/binaryope.hpp"
    #include "headers/identifier.hpp"
    #include "headers/vardeclaration.hpp"
    #include "headers/methodcall.hpp"
    #include "headers/booleancmp.hpp"
    #include "headers/if.hpp"
    #include "headers/boolean.hpp"

    using namespace april;

    extern int yylex();
    extern int yyerror(const char*);
    extern int line;
    extern int col;
    extern char* yytext;

    april::Block* programBlock = nullptr;    
%}

%union
{
    april::Expression* expr;
    april::Statement* stmt;
    april::Block* block;
    april::Identifier* ident;
    std::vector<april::Expression*> *exprvec;
    std::string* _string;
    int token;
}

%token <_string> TDIGIT TDOUBLE TIDENTIFIER TBOOLEAN
%token <token> TPLUS TMIN TMUL TDIV TJUMP TSC
%token <token> TLPAREN TRPAREN TSTR TLBRACE TRBRACE 
%token <token> TVAR TEQUAL TCOLON TCOMMA TAND TOR
%token <token> TCOMNE TCOMEQ TCOMLE TCOMGE TCOMLT TCOMGT
%token <token> TIF TELSE

%type <ident> ident
%type <expr> expr basic binary_ope method_call boolean_expr
%type <stmt> stmt  var_decl conditional
%type <block> program stmts block
%type <exprvec> call_args
%type <token> comparasion;

%left TPLUS TMIN
%left TMUL TDIV

%start program

%%

program: %empty                 { programBlock = new april::Block{}; }
    |   stmts                   { programBlock = $1; }
    ;

stmts: stmt                     { $$ = new april::Block(); $$->statements.push_back($<stmt>1); }
    | stmts stmt                { $$->statements.push_back($<stmt>2); }
    ;

stmt: expr TSC                  { $$ = new april::ExprStatement{$1}; }
    | var_decl                  { }
    | conditional               
    ;

conditional: TIF expr block					{ $$ = new april::If($2, $3); }
	| TIF expr block TELSE block			{ $$ = new april::If($2, $3, $5); }
	;

block: TLBRACE stmts TRBRACE				{ $$ = $2; }
	| TLBRACE TRBRACE						{ $$ = new april::Block();  }
    ;

var_decl: TVAR ident TCOLON ident TSC								{ $$ = new april::VarDeclaration($2, $4);}
    | TVAR ident TCOLON ident TEQUAL expr TSC                       { $$ = new april::VarDeclaration($2, $4, $6);}
    ;

expr: binary_ope                {  }
    | basic                     { $$ = $1; }
    | ident                     { $<ident>$ = $1; }
    | method_call               {  }
    | boolean_expr              {  }
    ;

boolean_expr: expr comparasion expr		    { $$ = new april::BooleanCmp($1, $2, $3);} 
	;

comparasion: TCOMNE | TCOMEQ | TCOMLE | TCOMGE | TCOMLT | TCOMGT
    ;

method_call: ident TLPAREN call_args TRPAREN       { $$ = new april::MethodCall($1, $3); }
    ;

call_args: %empty                           { $$ = new april::ExpressionList(); }
    | expr                                  { $$ = new april::ExpressionList(); $$->push_back($1); }
    | call_args TCOMMA expr                 { $$->push_back($3); }
    ;

binary_ope: expr TPLUS expr       { $$ = new april::BinaryOpe{ $1, april::OPE::PLUS, $3 }; }
    |   expr TMIN  expr           { $$ = new april::BinaryOpe{ $1, april::OPE::MIN, $3 }; }
    |   expr TMUL  expr           { $$ = new april::BinaryOpe{ $1, april::OPE::MUL, $3 }; }
    |   expr TDIV  expr           { $$ = new april::BinaryOpe{ $1, april::OPE::DIV, $3 }; }
    |   expr TAND  expr           { $$ = new april::BinaryOpe{ $1, april::OPE::AND, $3 }; }
    |   expr TOR  expr            { $$ = new april::BinaryOpe{ $1, april::OPE::OR, $3 }; }
    |   TLPAREN expr TRPAREN      { $$ = $2; }
    ;

basic: TDIGIT                       { $$ = new april::Integer{ std::atol($1->c_str()) }; delete $1; }
    |   TDOUBLE                     { $$ = new april::Double{ std::atof($1->c_str()) }; delete $1; }
    |   TMIN TDIGIT  %prec TDIV     { $$ = new april::Integer{ -std::atol($2->c_str()) }; delete $2; }
    |   TMIN TDOUBLE  %prec TDIV    { $$ = new april::Double{ -std::atof($2->c_str()) }; delete $2; }
    |   TBOOLEAN                    { $$ = new april::Boolean{ *$1 }; delete $1; }
    ;

ident: TIDENTIFIER                          { $$ = new april::Identifier(*$1); delete $1; }
    ; 

%%