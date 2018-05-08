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
<<<<<<< HEAD
    TPLUS = 261,
    TMIN = 262,
    TMUL = 263,
    TDIV = 264,
    TJUMP = 265,
    TSC = 266,
    TLPAREN = 267,
    TRPAREN = 268,
    TSTR = 269,
    TPOINT = 270,
    TLBRACKET = 271,
    TRBRACKET = 272,
=======
    TBOOLEAN = 261,
    TPLUS = 262,
    TMIN = 263,
    TMUL = 264,
    TDIV = 265,
    TJUMP = 266,
    TSC = 267,
    TLPAREN = 268,
    TRPAREN = 269,
    TSTR = 270,
    TLBRACE = 271,
    TRBRACE = 272,
>>>>>>> lorena
    TVAR = 273,
    TEQUAL = 274,
    TCOLON = 275,
    TCOMMA = 276,
    TAND = 277,
    TOR = 278,
<<<<<<< HEAD
    TCOMNE = 279,
    TCOMEQ = 280,
    TCOMLE = 281,
    TCOMGE = 282,
    TCOMLT = 283,
    TCOMGT = 284
=======
    TCOEQU = 279,
    TCOMNE = 280,
    TCOMEQ = 281,
    TCOMLE = 282,
    TCOMGE = 283,
    TCOMLT = 284,
    TCOMGT = 285,
    TIF = 286,
    TELSE = 287,
    TFOR = 288,
    TFN = 289,
    TASIGPLUS = 290,
    TASIGMINUS = 291,
    TASIGMULT = 292,
    TASIGDIV = 293,
    TNOT = 294
>>>>>>> lorena
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
<<<<<<< HEAD
#line 36 "parser.y" /* yacc.c:1909  */
=======
#line 40 "parser.y" /* yacc.c:1909  */
>>>>>>> lorena

    april::Expression* expr;
    april::Statement* stmt;
    april::Block* block;
    april::Identifier* ident;
    std::vector<april::Expression*> *exprvec;
    std::vector<april::VarDeclaration*> *vardecl;
    april::VarDeclaration* var_decl;
    std::string* _string;
    int token;

<<<<<<< HEAD
#line 94 "parser.h" /* yacc.c:1909  */
=======
#line 106 "parser.h" /* yacc.c:1909  */
>>>>>>> lorena
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
