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
    #include "headers/string.hpp"
    #include "headers/stringarray.hpp"
    #include "headers/binaryope.hpp"
    #include "headers/identifier.hpp"
    #include "headers/vardeclaration.hpp"
    #include "headers/methodcall.hpp"
    #include "headers/methodstruct.hpp"
    #include "headers/booleancmp.hpp"
    #include "headers/if.hpp"
    #include "headers/boolean.hpp"
    #include "headers/for.hpp"
    #include "headers/assignment.hpp"
    #include "headers/assigbioperator.hpp"
    #include "headers/not.hpp"
    #include "headers/function.hpp"
    #include "headers/vardeclarationdeduce.hpp"
    #include "headers/return.hpp"
    #include "headers/break.hpp"
    #include "headers/list.hpp"
    #include "headers/listaccess.hpp"
    #include "headers/assignmentlist.hpp"
    #include "headers/methodstruct.hpp"
    #include "headers/methodhandlelist.hpp"
    #include "headers/methodhandlestring.hpp"
    #include "headers/methodhandlecast.hpp"
    #include "headers/methodhandleio.hpp"
    
    
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
    std::vector<april::VarDeclaration*> *vardecl;
    april::VarDeclaration* var_decl;
    std::string* _string;
    int token;
}

%token <_string> TDIGIT TDOUBLE TIDENTIFIER TBOOLEAN
%token <token> TPLUS TMIN TMUL TDIV TJUMP TSC
%token <token> TLPAREN TRPAREN TSTR TLBRACE TRBRACE TPOINT TLBRACKET TRBRACKET
%token <token> TVAR TEQUAL TCOLON TCOMMA TAND TOR TCOEQU
%token <token> TCOMNE TCOMEQ TCOMLE TCOMGE TCOMLT TCOMGT
%token <token> TIF TELSE TFOR TFN TRETURN TBREAK
%token <token> TASIGPLUS TASIGMINUS TASIGMULT TASIGDIV TNOT

%type <ident> ident
%type <expr> expr basic binary_ope method_call boolean_expr logic_ope list_expr list_access
%type <stmt> stmt  var_decl conditional for fn_decl var_decl_arg  return break
%type <block> program stmts block
%type <exprvec> call_args list_elements
%type <token> comparasion;
%type <vardecl> fn_args;

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
    | for      
    | fn_decl  
    | return    
    | break
    ;

break: TBREAK TSC   { $$ = new april::Break{}; }
    ;

return: TRETURN expr TSC                    { $$ = new april::Return{$2}; }    
    ;

fn_decl: TFN ident TLPAREN fn_args TRPAREN block       { $$ = new april::Function{$2, $4, $6}; }
    ;

fn_args: %empty                             { $$ = new april::VarList(); }
    |   var_decl_arg                        { $$ = new april::VarList(); $$->push_back($<var_decl>1); }
    |   fn_args TCOMMA var_decl_arg         { $1->push_back($<var_decl>3); }
    ;

var_decl_arg: ident TCOLON ident            { $$ = new april::VarDeclaration{$1, $3};}
    ;

for: TFOR expr block                        { $$ = new april::For{$2, $3}; }
    ;

conditional: TIF expr block					{ $$ = new april::If{$2, $3}; }
	| TIF expr block TELSE block			{ $$ = new april::If{$2, $3, $5}; }
	;

block: TLBRACE stmts TRBRACE				{ $$ = $2; }
	| TLBRACE TRBRACE						{ $$ = new april::Block{};  }
    ;

var_decl: TVAR ident TCOLON ident TSC								{ $$ = new april::VarDeclaration{$2, $4};}
    | TVAR ident TCOLON ident TEQUAL expr TSC                       { $$ = new april::VarDeclaration{$2, $4, $6};}
    | ident TCOEQU expr TSC                                         { $$ = new april::VarDeclarationDeduce{$1, $3}; }
    ;

expr: binary_ope                {  }
    | ident TEQUAL expr         { $$ = new april::Assignment{$<ident>1, $3}; }
    | list_access TEQUAL expr   { $$ = new april::AssignmentList{$1, $3}; }
    | ident TASIGPLUS expr		{ $$ = new april::AssigBioperator{ $1, april::OPE::PLUS, $3 }; }
    | ident TASIGMINUS expr		{ $$ = new april::AssigBioperator{ $1, april::OPE::MIN, $3 }; }
    | ident TASIGMULT expr		{ $$ = new april::AssigBioperator{ $1, april::OPE::MUL, $3 }; }
    | ident TASIGDIV expr       { $$ = new april::AssigBioperator{ $1, april::OPE::DIV, $3 }; }
    | basic                     { $$ = $1; }
    | ident                     { $<ident>$ = $1; }
    | method_call               {  }
    | boolean_expr              {  }
    | logic_ope                 {  }
    | list_expr                 {  }
    | list_access               {  }
    ;

list_expr: TLBRACKET list_elements TRBRACKET		{ $$ = new april::List($2); }
    ;

list_elements: %empty					    { $$ = new april::ExpressionList(); }
	| expr								    { $$ = new april::ExpressionList(); $$->push_back($1); }
	| list_elements TCOMMA expr			    { $$->push_back($3); }
    ;

list_access: ident TLBRACKET expr TRBRACKET			{ $$ = new april::ListAccess{$1, $3}; }
	| list_access TLBRACKET expr TRBRACKET			{ $$ = new april::ListAccess{$1, $3}; }
    ;

logic_ope: TNOT expr 			            { $$ = new april::Not{ $2 }; }
    ;

boolean_expr: expr comparasion expr		    { $$ = new april::BooleanCmp{$1, $2, $3};} 
	;

comparasion: TCOMNE | TCOMEQ | TCOMLE | TCOMGE | TCOMLT | TCOMGT
    ;

method_call: ident TLPAREN call_args TRPAREN       { $$ = new april::MethodCall( $1, $3 ); }
    | ident TPOINT ident TLPAREN call_args TRPAREN { $$ = new april::MethodStruct( $1, $3, $5 ); }
    | expr TPOINT ident TLPAREN call_args TRPAREN { $$ = new april::MethodStruct( $1, $3, $5 ); }
    ;

call_args: %empty                           { $$ = new april::ExpressionList(); }
    | call_args TCOMMA expr                 { $$->push_back($3); }
    | expr                                  { $$ = new april::ExpressionList(); $$->push_back($1); }
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
    |   TSTR                        { $$ = new april::String(yytext); }
    ;   
    |   TBOOLEAN                    { $$ = new april::Boolean{ *$1 }; delete $1; }
    ;

ident: TIDENTIFIER                          { $$ = new april::Identifier{*$1}; delete $1; }
    ; 

%%