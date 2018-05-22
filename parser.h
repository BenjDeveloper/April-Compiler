/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    TSTR = 262,
    TPLUS = 263,
    TMIN = 264,
    TMUL = 265,
    TDIV = 266,
    TJUMP = 267,
    TSC = 268,
    TMOD = 269,
    TGLOBAL = 270,
    TLPAREN = 271,
    TRPAREN = 272,
    TLBRACE = 273,
    TRBRACE = 274,
    TPOINT = 275,
    TLBRACKET = 276,
    TRBRACKET = 277,
    TVAR = 278,
    TEQUAL = 279,
    TCOLON = 280,
    TCOMMA = 281,
    TAND = 282,
    TOR = 283,
    TCOEQU = 284,
    TCOMNE = 285,
    TCOMEQ = 286,
    TCOMLE = 287,
    TCOMGE = 288,
    TCOMLT = 289,
    TCOMGT = 290,
    TIF = 291,
    TELSE = 292,
    TFOR = 293,
    TFN = 294,
    TRETURN = 295,
    TBREAK = 296,
    TASIGPLUS = 297,
    TASIGMINUS = 298,
    TASIGMULT = 299,
    TASIGDIV = 300,
    TNOT = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 55 "parser.y" /* yacc.c:1909  */

    april::Expression* expr;
    april::Statement* stmt;
    april::Block* block;
    april::Identifier* ident;
    std::vector<april::Expression*> *exprvec;
    std::vector<april::VarDeclaration*> *vardecl;
    april::VarDeclaration* var_decl;
    std::string* _string;
    int token;

#line 113 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
