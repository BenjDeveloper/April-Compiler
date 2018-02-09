%option noyywrap
%{
    #include <iostream>
    #include "node.h"
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
\".*\"              { return TOKEN(TSTR); }
"/*"[^"*/"]*"*/"    { line++; col=0; }
\/\/.*?\n?           { line++; }
{DIGIT}             { SAVE_TOKEN; return TDIGIT; }
{DOUBLE}            { SAVE_TOKEN; return TDOUBLE; } 
"var"               { return TOKEN(TLET); }
{IDENTIFIER}        { SAVE_TOKEN; return TIDENTIFIER; }
"("                 { return TOKEN(TLPAREN); }
")"                 { return TOKEN(TRPAREN); }
":="                { return TOKEN(TCEQUAL); }
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