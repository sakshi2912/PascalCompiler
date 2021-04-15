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
    WHILE = 285,                   /* WHILE  */
    INT = 286,                     /* INT  */
    CHAR = 287,                    /* CHAR  */
    FLOAT = 288,                   /* FLOAT  */
    DOUBLE = 289,                  /* DOUBLE  */
    VOID = 290,                    /* VOID  */
    BOOL = 291,                    /* BOOL  */
    COUT = 292,                    /* COUT  */
    COUTSTR = 293,                 /* COUTSTR  */
    INS = 294,                     /* INS  */
    CIN = 295,                     /* CIN  */
    XTR = 296,                     /* XTR  */
    IF = 297,                      /* IF  */
    ELSE = 298,                    /* ELSE  */
    DO = 299,                      /* DO  */
    FOR = 300,                     /* FOR  */
    ELSE_IF = 301,                 /* ELSE_IF  */
    T_RETURN = 302,                /* T_RETURN  */
    ID = 303,                      /* ID  */
    NUM = 304,                     /* NUM  */
    SINGLE_CHAR_VALUE = 305,       /* SINGLE_CHAR_VALUE  */
    OPB = 306,                     /* OPB  */
    CLB = 307,                     /* CLB  */
    OSCOPE = 308,                  /* OSCOPE  */
    CSCOPE = 309                   /* CSCOPE  */
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
#define WHILE 285
#define INT 286
#define CHAR 287
#define FLOAT 288
#define DOUBLE 289
#define VOID 290
#define BOOL 291
#define COUT 292
#define COUTSTR 293
#define INS 294
#define CIN 295
#define XTR 296
#define IF 297
#define ELSE 298
#define DO 299
#define FOR 300
#define ELSE_IF 301
#define T_RETURN 302
#define ID 303
#define NUM 304
#define SINGLE_CHAR_VALUE 305
#define OPB 306
#define CLB 307
#define OSCOPE 308
#define CSCOPE 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
