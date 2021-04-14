/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    HEADER = 258,                  /* HEADER  */
    VAR = 259,                     /* VAR  */
    MAIN = 260,                    /* MAIN  */
    TO = 261,                      /* TO  */
    DOWN_TO = 262,                 /* DOWN_TO  */
    THEN = 263,                    /* THEN  */
    T_lt = 264,                    /* T_lt  */
    T_gt = 265,                    /* T_gt  */
    T_lteq = 266,                  /* T_lteq  */
    T_gteq = 267,                  /* T_gteq  */
    T_neq = 268,                   /* T_neq  */
    T_eqeq = 269,                  /* T_eqeq  */
    T_pl = 270,                    /* T_pl  */
    T_min = 271,                   /* T_min  */
    T_mul = 272,                   /* T_mul  */
    T_div = 273,                   /* T_div  */
    T_and = 274,                   /* T_and  */
    T_or = 275,                    /* T_or  */
    T_incr = 276,                  /* T_incr  */
    T_decr = 277,                  /* T_decr  */
    T_not = 278,                   /* T_not  */
    T_eq = 279,                    /* T_eq  */
    T_assign = 280,                /* T_assign  */
    T_comma = 281,                 /* T_comma  */
    T_semi = 282,                  /* T_semi  */
    T_dot = 283,                   /* T_dot  */
    T_END = 284,                   /* T_END  */
    INT = 285,                     /* INT  */
    CHAR = 286,                    /* CHAR  */
    FLOAT = 287,                   /* FLOAT  */
    DOUBLE = 288,                  /* DOUBLE  */
    VOID = 289,                    /* VOID  */
    BOOL = 290,                    /* BOOL  */
    COUT = 291,                    /* COUT  */
    COUTSTR = 292,                 /* COUTSTR  */
    INS = 293,                     /* INS  */
    CIN = 294,                     /* CIN  */
    XTR = 295,                     /* XTR  */
    IF = 296,                      /* IF  */
    ELSE = 297,                    /* ELSE  */
    DO = 298,                      /* DO  */
    FOR = 299,                     /* FOR  */
    ELSE_IF = 300,                 /* ELSE_IF  */
    T_RETURN = 301,                /* T_RETURN  */
    ID = 302,                      /* ID  */
    NUM = 303,                     /* NUM  */
    SINGLE_CHAR_VALUE = 304,       /* SINGLE_CHAR_VALUE  */
    OPB = 305,                     /* OPB  */
    CLB = 306,                     /* CLB  */
    OSCOPE = 307,                  /* OSCOPE  */
    CSCOPE = 308                   /* CSCOPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define HEADER 258
#define VAR 259
#define MAIN 260
#define TO 261
#define DOWN_TO 262
#define THEN 263
#define T_lt 264
#define T_gt 265
#define T_lteq 266
#define T_gteq 267
#define T_neq 268
#define T_eqeq 269
#define T_pl 270
#define T_min 271
#define T_mul 272
#define T_div 273
#define T_and 274
#define T_or 275
#define T_incr 276
#define T_decr 277
#define T_not 278
#define T_eq 279
#define T_assign 280
#define T_comma 281
#define T_semi 282
#define T_dot 283
#define T_END 284
#define INT 285
#define CHAR 286
#define FLOAT 287
#define DOUBLE 288
#define VOID 289
#define BOOL 290
#define COUT 291
#define COUTSTR 292
#define INS 293
#define CIN 294
#define XTR 295
#define IF 296
#define ELSE 297
#define DO 298
#define FOR 299
#define ELSE_IF 300
#define T_RETURN 301
#define ID 302
#define NUM 303
#define SINGLE_CHAR_VALUE 304
#define OPB 305
#define CLB 306
#define OSCOPE 307
#define CSCOPE 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
