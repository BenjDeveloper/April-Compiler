%{
    #include <iostream>
    #include <algorithm>
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
	#include "include/scope.hpp"
    #include "include/forloop.hpp"    
    #include "include/function.hpp"    
    #include "include/return.hpp"   
    #include "include/assigbiope.hpp"
	#include "parser.h"
    

    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
    
    extern "C" int yywrap() { return 1; }
  	
    april::STRUCINFO* april_errors = new april::STRUCINFO{1, "empty"};
      
    int line = 1;
    int col = 0;

    int yyerror(const char* msg)
    {
        std::cout << april_errors->file_name <<":" << april_errors->line  <<" error: " << msg << std::endl;
        return 1;
    }


%}

DIGIT        [0-9]+
DOUBLE       [0-9]*\.[0-9]+
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*
%%

[\n]                { april_errors->line++; col = 0; }
[\t]                { col++; }
\"(.*)\"            { return TOKEN(TSTR); }
\/\*(.*\n*)*\*\/    { april_errors->line++; col=0; }
\/\/.*?             { /*empty*/ }
\/\/.*?\n           { april_errors->line++; }
"true"              { SAVE_TOKEN; return TBOOLEAN; }
{DIGIT}             { SAVE_TOKEN; return TDIGIT; }
{DOUBLE}            { SAVE_TOKEN; return TDOUBLE; } 
"false"             { SAVE_TOKEN; return TBOOLEAN; }
"var"               { return TOKEN(TVAR); }
"and"				{ return TOKEN(TAND); }
"or"				{ return TOKEN(TOR); }
"not"				{ return TOKEN(TNOT); }
"if"				{ return TOKEN(TIF); }
"else"				{ return TOKEN(TELSE); }
"for"               { return TOKEN(TFOR); }
"fn"                { return TOKEN(TFN); }
"return"            { return TOKEN(TRETURN); }
"!="				{ return TOKEN(TCOMNE); }
"=="				{ return TOKEN(TCOMEQ); }
"<="				{ return TOKEN(TCOMLE); }
">="				{ return TOKEN(TCOMGE); }
"<"					{ return TOKEN(TCOMLT); }
">"					{ return TOKEN(TCOMGT); }
"("                 { return TOKEN(TLPAREN); }
")"                 { return TOKEN(TRPAREN); }
":="                { return TOKEN(TCOEQU); }
"+="                { return TOKEN(TASIGPLUS); }
"-="                { return TOKEN(TASIGMINUS); }
"*="                { return TOKEN(TASIGMULT); }
"/="                { return TOKEN(TASIGDIV); }
":"                 { return TOKEN(TCOLON); }
"="                 { return TOKEN(TEQUAL); }
";"                 { return TOKEN(TSC); }
"{"                 { return TOKEN(TLBRACE); }
"}"                 { return TOKEN(TRBRACE); }
"+"                 { return TOKEN(TPLUS); }
"-"                 { return TOKEN(TMIN); }
"/"                 { return TOKEN(TDIV); }
"*"                 { return TOKEN(TMUL); }
","                 { return TOKEN(TCOMMA); }
{IDENTIFIER}        { SAVE_TOKEN; return TIDENTIFIER; }
.                   { /*empty*/ }
%%
