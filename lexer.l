%{
    #include <iostream>
    #include <algorithm>
    #include "headers/node.hpp"
    #include "headers/statement.hpp"
    #include "headers/expression.hpp"
    #include "headers/exprstatement.hpp"
    #include "headers/block.hpp"
    #include "headers/codegencontext.hpp"
    #include "headers/integer.hpp"
    #include "headers/double.hpp"
    #include "headers/string.hpp"
    #include "headers/binaryope.hpp"
    #include "headers/identifier.hpp"
    #include "headers/vardeclaration.hpp"
    #include "headers/methodcall.hpp"
    #include "parser.h"

    #define SAVE_TOKEN yylval._string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)

    extern "C" yywrap() { return 1; }

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
\"(.*)\"            { return TOKEN(TSTR); }
\/\*(.*\n*)*\*\/    { april_errors->line++; col=0; }
\/\/.*?             { /*empty*/ }
\/\/.*?\n           { april_errors->line++; }
{DIGIT}             { SAVE_TOKEN; return TDIGIT; }
{DOUBLE}            { SAVE_TOKEN; return TDOUBLE; }
"var"               { return TOKEN(TVAR); }
":"                 { return TOKEN(TCOLON); }
"="                 { return TOKEN(TEQUAL); }
"+"                 { return TOKEN(TPLUS); }
"-"                 { return TOKEN(TMIN); }
"*"                 { return TOKEN(TMUL); }
"/"                 { return TOKEN(TDIV); }
"("                 { return TOKEN(TLPAREN); }
")"                 { return TOKEN(TRPAREN); }
";"                 { return TOKEN(TSC); }
","                 { return TOKEN(TCOMMA); }
{IDENTIFIER}        { SAVE_TOKEN; return TIDENTIFIER; }
.                   { /*empty*/ }
%%