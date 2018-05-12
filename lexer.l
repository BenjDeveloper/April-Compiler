%{
    #include <iostream>
    #include <algorithm>
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
    #include "headers/methodhandle.hpp"
    #include "headers/booleancmp.hpp"
    #include "headers/if.hpp"
    #include "headers/boolean.hpp"
    #include "headers/for.hpp"
    #include "headers/assignment.hpp"
    #include "headers/assigbioperator.hpp"
    #include "headers/not.hpp"  
    #include "headers/function.hpp"
    #include "headers/vardeclarationdeduce.hpp"
    #include "parser.h"

    #define SAVE_TOKEN yylval._string = new std::string(yytext, yyleng)
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

DIGIT       [0-9]+
DOUBLE      [0-9]*\.[0-9]+
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*

%%

[\n]                { april_errors->line++; col = 0; }
[\t]                { col++; }
\"([^\\\"]|\\.)*\"  { return TOKEN(TSTR); }
\/\*(.*\n*)*\*\/    { april_errors->line++; col=0; }
\/\/.*?             { /*empty*/ }
\/\/.*?\n           { april_errors->line++; }
{DIGIT}             { SAVE_TOKEN; return TDIGIT; }
{DOUBLE}            { SAVE_TOKEN; return TDOUBLE; }
"var"               { return TOKEN(TVAR); }
"for"               { return TOKEN(TFOR); }
"if"                { return TOKEN(TIF); }
"else"              { return TOKEN(TELSE); }
"true"              { SAVE_TOKEN; return TBOOLEAN; }
"false"             { SAVE_TOKEN; return TBOOLEAN; }
"and"               { return TOKEN(TAND); }
"or"                { return TOKEN(TOR); }
"not"               { return TOKEN(TNOT); }
"fn"                { return TOKEN(TFN); }
":="                { return TOKEN(TCOEQU); }
":"                 { return TOKEN(TCOLON); }
"="                 { return TOKEN(TEQUAL); }
"+"                 { return TOKEN(TPLUS); }
"-"                 { return TOKEN(TMIN); }
"*"                 { return TOKEN(TMUL); }
"/"                 { return TOKEN(TDIV); }
"."                 { return TOKEN(TPOINT); }
"("                 { return TOKEN(TLPAREN); }
")"                 { return TOKEN(TRPAREN); }
"["                 { return TOKEN(TLBRACKET); }
"]"                 { return TOKEN(TRBRACKET); }
"{"                 { return TOKEN(TLBRACE); }
"}"                 { return TOKEN(TRBRACE); }
";"                 { return TOKEN(TSC); }
","                 { return TOKEN(TCOMMA); }
"!="				{ return TOKEN(TCOMNE); }
"=="				{ return TOKEN(TCOMEQ); }
"<="				{ return TOKEN(TCOMLE); }
">="				{ return TOKEN(TCOMGE); }
"<"					{ return TOKEN(TCOMLT); }
">"                 { return TOKEN(TCOMGT); }
"+="                { return TOKEN(TASIGPLUS); }
"-="                { return TOKEN(TASIGMINUS); }
"*="                { return TOKEN(TASIGMULT); }
"/="                { return TOKEN(TASIGDIV); }
{IDENTIFIER}        { SAVE_TOKEN; return TIDENTIFIER; }
.                   { /*empty*/ }
%%