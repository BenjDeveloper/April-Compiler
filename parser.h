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
    TPLUS = 262,
    TMIN = 263,
    TMUL = 264,
    TDIV = 265,
    TVAR = 266,
    TAMPER = 267,
    TCOLON = 268,
    TEQUAL = 269,
    TSC = 270,
    TJUMP = 271,
    TCOMMA = 272,
    TCOEQU = 273,
    TRBRACE = 274,
    TLBRACE = 275,
    TLPAREN = 276,
    TRPAREN = 277,
    TSTR = 278,
    TLBRACKET = 279,
    TRBRACKET = 280,
    TCOMNE = 281,
    TCOMEQ = 282,
    TCOMLE = 283,
    TCOMGE = 284,
    TCOMLT = 285,
    TCOMGT = 286,
    TAND = 287,
    TOR = 288,
    TNOT = 289,
    TIF = 290,
    TELSE = 291,
    TFOR = 292,
    TFN = 293,
    TRETURN = 294,
    TASIGPLUS = 295,
    TASIGMINUS = 296,
    TASIGMULT = 297,
    TASIGDIV = 298,
    TUNARIPLUS = 299,
    TUNARIMIN = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 46 "src/parser.y" /* yacc.c:1909  */

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

#line 113 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
