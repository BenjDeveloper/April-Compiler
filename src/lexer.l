%option noyywrap
%{
    #include <iostream>
    #include <algorithm>
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
    #include "parser.h"
    

    #define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
    #define TOKEN(t) (yylval.token = t)
    int line = 1;
    int col = 0;

%}

DIGIT       [0-9]+
DOUBLE       [0-9]*\.[0-9]+
IDENTIFIER   [a-zA-Z_][a-zA-Z0-9_]*

%%

[\n]                {line++; col = 0; }
[\t]                { col++; }
\"(.*)\"            { return TOKEN(TSTR); }
"/*"[^"*/"]*"*/"    { line++; col=0; }
{DIGIT}             { SAVE_TOKEN; return TDIGIT; }
{DOUBLE}            { SAVE_TOKEN; return TDOUBLE; } 
"let"               { return TOKEN(TLET); }
{IDENTIFIER}        { SAVE_TOKEN; return TIDENTIFIER; }
"("                 { return TOKEN(TLPAREN); }
")"                 { return TOKEN(TRPAREN); }
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
.                   { /* std::cout << "error en la linea: " << line << ": " << col << std::endl; yyterminate(); */ }
%%