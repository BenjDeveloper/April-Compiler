/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TDIGIT = 258,
    TDOUBLE = 259,
    TIDENTIFIER = 260,
    TBOOLEAN = 261,
    TPLUS = 262,
    TMIN = 263,
    TMUL = 264,
    TDIV = 265,
    TVAR = 266,
    TAMPER = 267,
    TGLOBAL = 268,
    TCOLON = 269,
    TEQUAL = 270,
    TSC = 271,
    TJUMP = 272,
    TCOMMA = 273,
    TCOEQU = 274,
    TLTL = 275,
    TRBRACE = 276,
    TLBRACE = 277,
    TLPAREN = 278,
    TRPAREN = 279,
    TSTR = 280,
    TLBRACKET = 281,
    TRBRACKET = 282,
    TCOMNE = 283,
    TCOMEQ = 284,
    TCOMLE = 285,
    TCOMGE = 286,
    TCOMLT = 287,
    TCOMGT = 288,
    TAND = 289,
    TOR = 290,
    TNOT = 291,
    TIF = 292,
    TELSE = 293,
    TFOR = 294,
    TFN = 295,
    TRETURN = 296,
    TASIGPLUS = 297,
    TASIGMINUS = 298,
    TASIGMULT = 299,
    TASIGDIV = 300,
    TUNARIPLUS = 301,
    TUNARIMIN = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 49 "src/parser.y" /* yacc.c:1909  */

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

#line 115 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
