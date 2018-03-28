    %defines "parser.h"

%{
    #include <iostream>
    #include <cstring>
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
    #include "include/function.hpp"
    #include "include/return.hpp"
    #include "include/assigbiope.hpp"
    #include "include/logicope.hpp"
    #include "include/array.hpp"
    #include "include/arrayaccess.hpp"
    #include "include/assignmentarray.hpp"


    using namespace april;
    
    extern int yylex();
    extern int yyerror(const char*);
    extern int line;
    extern int col;
    extern char* yytext;

    april::Block* programBlock;
    bool existMainFunction = false;
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
    std::vector<april::VariableDeclaration*> *vardecl;
    int token;
}

%token <string> TDIGIT TDOUBLE TIDENTIFIER TBOOLEAN 
%token <token> TPLUS TMIN TMUL TDIV TVAR
%token <token> TCOLON TEQUAL TSC TJUMP TCOMMA TCOEQU
%token <token> TRBRACE TLBRACE
%token <token> TLPAREN TRPAREN TSTR TLBRACKET TRBRACKET
%token <token> TCOMNE TCOMEQ TCOMLE TCOMGE TCOMLT TCOMGT
%token <token> TAND TOR TNOT
%token <token> TIF TELSE TFOR TFN TRETURN
%token <token> TASIGPLUS TASIGMINUS TASIGMULT TASIGDIV
%token <token> TUNARIPLUS TUNARIMIN

%type <ident> ident
%type <exprvec> call_args array_elements
%type <expr> expr binary_ope_expr basics boolean_expr unary_ope method_call logic_ope array_expr array_access array_declaration
%type <stmt> stmt var_decl conditional scope for fn_decl var_decl_arg return 
%type <block> program stmts block
%type <token> comparasion
%type <vardecl> fn_args;

%left TPLUS TMIN
%left TMUL TDIV

%start program

%%

program: /* blank */                        { programBlock = new april::Block();}
    | stmts                                 { programBlock = $1; }
	;

stmts: stmt                                 { $$ = new april::Block(); $$->statements.push_back($<stmt>1); }
    |  stmts stmt                           { $1->statements.push_back($<stmt>2); }
	;

stmt: var_decl                              { }
    | expr TSC                              { $$ = new april::ExpressionStatement($1); }
    | conditional
	| scope
	| for
    | fn_decl
    | var_decl_arg
    | return
    ;

return: TRETURN  TSC                        { $$ = new april::Return(); }
    |   TRETURN expr TSC                    { $$ = new april::Return($2); }    
    ;

fn_decl: TFN ident TLPAREN fn_args TRPAREN TCOLON ident block       { $$ = new april::Function($7, $2, $4, $8); }
    ;

fn_args: /* blank */                        { $$ = new april::VarList(); }
    |   var_decl_arg                        { $$ = new april::VarList(); $$->push_back($<var_decl>1); }
    |   fn_args TCOMMA var_decl_arg         { $1->push_back($<var_decl>3); }
    ;

var_decl_arg: ident TCOLON ident            { $$ = new april::VariableDeclaration(*$3, *$1);}
    ;

for: TFOR expr block                        { $$ = new april::ForLoop($2, $3); }
    ;

scope: block			                    { $$ = new april::Scope($1); }
	;

conditional: TIF expr block					{ $$ = new april::Conditional($2, *$3); }
	| TIF expr block TELSE block			{ $$ = new april::Conditional($2,* $3, *$5); }
	;

block: TLBRACE stmts TRBRACE				{ $$ = $2; }
	| TLBRACE TRBRACE						{ $$ = new april::Block();  }
	;

var_decl: TVAR ident TCOLON ident TSC                       { $$ = new april::VariableDeclaration(*$4, *$2);}
	| TVAR ident TCOLON array_declaration TSC				{  }
    | TVAR ident TCOLON ident TEQUAL expr TSC               { $$ = new april::VariableDeclaration(*$4, *$2, $6); }
    | TVAR ident TCOLON ident TEQUAL method_call TSC        { $$ = new april::VariableDeclaration(*$4, *$2, $6); }
    | ident TCOEQU expr TSC                                 { $$ = new april::VariableDeclarationDeduce(*$1, $3); }
    | ident TCOEQU method_call  TSC                         { $$ = new april::VariableDeclarationDeduce(*$1, $3); }
    ;

expr: binary_ope_expr									{ }
    | ident TEQUAL expr									{ $$ = new april::Assignment(*$<ident>1, *$3); }
    | ident TEQUAL method_call							{ $$ = new april::Assignment(*$<ident>1, *$3); }
    | array_access TEQUAL expr							{ $$ = new april::AssignmentArray($1, $3);     }
    | ident TASIGPLUS expr								{ $$ = new april::AssigBioperator($1, $2, $3); }
    | ident TASIGMINUS expr								{ $$ = new april::AssigBioperator($1, $2, $3); }
    | ident TASIGMULT expr								{ $$ = new april::AssigBioperator($1, $2, $3); }
    | ident TASIGDIV expr								{ $$ = new april::AssigBioperator($1, $2, $3); }
    | basics											{ $$ = $1; }
    | ident												{ $<ident>$ = $1; }                            
    | boolean_expr										{ }
	| unary_ope											{ }
    | logic_ope											{ }
    | method_call										{ }
	| array_expr										{ }
	| array_access										{ }
	;

array_declaration: TLBRACKET TDIGIT TRBRACKET			{  }	
	| array_declaration ident							{  }
	;

array_access: ident TLBRACKET TDIGIT TRBRACKET			{ $$ = new april::ArrayAccess($1, std::atol($3->c_str())); delete $3; }
	| array_access TLBRACKET TDIGIT TRBRACKET			{ $$ = new april::ArrayAccess($1, std::atol($3->c_str())); delete $3; }
	;

array_elements: /* blank */					{ $$ = new april::ExpressionList(); }
	| expr								    { $$ = new april::ExpressionList(); $$->push_back($1); }
	| array_elements TCOMMA expr			{ $$->push_back($3); }
	;

array_expr: TLBRACKET array_elements TRBRACKET		{ $$ = new april::Array($2); }
	;

method_call: ident TLPAREN call_args TRPAREN       { $$ = new april::MethodCall($1, $3); }
    ;

logic_ope: TNOT expr 			            { $$ = new april::LogicOpe($1, $2); }
    ;

unary_ope: ident TUNARIPLUS    		        { $$ = new april::UnaryOpe($2, $1, $1); }
    | ident TUNARIMIN    	                { $$ = new april::UnaryOpe($2, $1, $1); }
    ;

call_args: /* blank */                      { $$ = new april::ExpressionList(); }
    | expr                                  { $$ = new april::ExpressionList(); $$->push_back($1); }
    | call_args TCOMMA expr                 { $$->push_back($3); }
    ;

binary_ope_expr: expr TPLUS expr            { $$ = new april::BinaryOperator(*$1, $2, *$3); } 
    | expr TMIN expr                        { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TMUL expr                        { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | expr TDIV expr                        { $$ = new april::BinaryOperator(*$1, $2, *$3); }
	| expr TAND expr					    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
	| expr TOR expr						    { $$ = new april::BinaryOperator(*$1, $2, *$3); }
    | TLPAREN expr TRPAREN                  { $$ = $2; }
    ;

boolean_expr: expr comparasion expr		    { $$ = new april::ComparasionOpe(*$1, $2, *$3);} 
	;

comparasion: TCOMNE | TCOMEQ | TCOMLE | TCOMGE | TCOMLT | TCOMGT
	;

basics: TDIGIT                              { $$ = new april::Integer(std::atol($1->c_str())); delete $1; }
    |   TMIN TDIGIT  %prec TDIV             { 
												char* value = new char(std::strlen($2->c_str())+2);
                                                std::strcpy(value, "-");
                                                std::strcat(value, $2->c_str());
                                                $$ = new april::Integer(std::atol(value)); 
                                                
												//delete $2; 
                                                //delete value;
											}
    |   TDOUBLE                             { $$ = new april::Double(std::atof($1->c_str())); delete $1; }
    |   TMIN TDOUBLE %prec TDIV             { 
                                                char* value = new char(std::strlen($2->c_str())+2);
                                                std::strcpy(value, "-");
                                                std::strcat(value, $2->c_str());
                                                $$ = new april::Double(std::atof(value)); 
                                                delete $2; 
                                                delete value; 
                                            }
    |   TSTR                                { $$ = new april::String(yytext); }
    |   TBOOLEAN                            { $$ = new april::Boolean(*$1); delete $1; }
    ;

ident: TIDENTIFIER                          { $$ = new april::Identifier(*$1); delete $1; }
%%
