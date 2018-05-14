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
    TJUMP = 266,
    TSC = 267,
    TLPAREN = 268,
    TRPAREN = 269,
    TSTR = 270,
    TLBRACE = 271,
    TRBRACE = 272,
    TPOINT = 273,
<<<<<<< HEAD
    TLBRACKET = 274,
    TRBRACKET = 275,
    TVAR = 276,
    TEQUAL = 277,
    TCOLON = 278,
    TCOMMA = 279,
    TAND = 280,
    TOR = 281,
    TCOEQU = 282,
    TCOMNE = 283,
    TCOMEQ = 284,
    TCOMLE = 285,
    TCOMGE = 286,
    TCOMLT = 287,
    TCOMGT = 288,
    TIF = 289,
    TELSE = 290,
    TFOR = 291,
    TFN = 292,
    TASIGPLUS = 293,
    TASIGMINUS = 294,
    TASIGMULT = 295,
    TASIGDIV = 296,
    TNOT = 297
=======
    TVAR = 274,
    TEQUAL = 275,
    TCOLON = 276,
    TCOMMA = 277,
    TAND = 278,
    TOR = 279,
    TCOEQU = 280,
    TCOMNE = 281,
    TCOMEQ = 282,
    TCOMLE = 283,
    TCOMGE = 284,
    TCOMLT = 285,
    TCOMGT = 286,
    TIF = 287,
    TELSE = 288,
    TFOR = 289,
    TFN = 290,
    TRETURN = 291,
    TBREAK = 292,
    TLBRACKET = 293,
    TRBRACKET = 294,
    TASIGPLUS = 295,
    TASIGMINUS = 296,
    TASIGMULT = 297,
    TASIGDIV = 298,
    TNOT = 299
>>>>>>> lorena
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
<<<<<<< HEAD
#line 44 "parser.y" /* yacc.c:1909  */
=======
#line 49 "parser.y" /* yacc.c:1909  */
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
#line 109 "parser.h" /* yacc.c:1909  */
=======
#line 111 "parser.h" /* yacc.c:1909  */
>>>>>>> lorena
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
