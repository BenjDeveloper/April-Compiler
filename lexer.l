%option noyywrap

%{

#include <iostream>
#include "parser.h"

%}

FLOAT           [0-9]+\.[0-9]+
INT             [0-9]+
OPERADORES      [+\-\*/()]


%%

{FLOAT}         { yylval._FLOAT = atof(yytext); return FLOAT; }
{INT}           { yylval._INT = atoi(yytext); return INT; }
{OPERADORES}    { return yytext[0]; }
"\n"            { return '\n'; }
.               { }

%%