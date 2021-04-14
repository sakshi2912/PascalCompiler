/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30705

/* Bison version string.  */
#define YYBISON_VERSION "3.7.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "yacc.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYSTYPE char*
int yylex();
void yyerror(char *s);
int top=-1;
int temp_i=0;
char tmp_i[3];
char temp[2]="t";
int ltop=0;
int label[20];
int lnum=0;
int l_for=0;


typedef struct node
{
	int line;
    int scope;
	char* name;
	char* value;
	char* type; 
} node;
typedef struct quadruples
{
    char *op;
    char *arg1;
    char *arg2;
    char *res;
}quad;
int quadlen = 0;
quad q[100];

    node symbol_table[100];
    int table_index;
    extern int yylineno;
    extern int scope;
    extern char name[100];
    extern char type[100];
    extern char value[100];

    void make_node(int line, char* name, char* value, char* type, int scope);
	void add_update_node(int line,char* name,char* value,char* type, int scope);
    void update(int line,char* name,char* value,char* type, int scope);
	void print_table();
	void push_sign();
	void push_lit(char* yy);
	void codegen_assign();
	void codegen();
	void codegen_assigna();
	void codegen_un();
	void if1();
	void if2();
	void if3();
	void while1();
	void while2();
	void while3();
	void for1();
	void for2();
	void for3();
	void for4();
    void make_node(int line, char* name, char* value, char* type, int scope)
    {
        symbol_table[table_index].name=(char*)malloc(sizeof(char)*strlen(name));
        symbol_table[table_index].value=(char*)malloc(sizeof(char)*strlen(value));
        symbol_table[table_index].type=(char*)malloc(sizeof(char)*strlen(type));
        symbol_table[table_index].line=line;
        symbol_table[table_index].scope=scope;
        strcpy(symbol_table[table_index].name,name);
		strcpy(symbol_table[table_index].value,value);
		strcpy(symbol_table[table_index].type,type);
        symbol_table[table_index].line=line;

    }
    void make_temp_node(char* name, char* value, char* type, int scope)
    {
        symbol_table[table_index].name=(char*)malloc(sizeof(char)*strlen(name));
        symbol_table[table_index].value=(char*)malloc(sizeof(char)*strlen(value));
        symbol_table[table_index].type=(char*)malloc(sizeof(char)*strlen(type));
        //symbol_table[table_index].line=line;
        symbol_table[table_index].scope=scope;
        strcpy(symbol_table[table_index].name,name);
		strcpy(symbol_table[table_index].value,value);
		strcpy(symbol_table[table_index].type,type);
        //symbol_table[table_index].line=line;

    }
    void add_update_node(int line,char* name,char* value,char* type, int scope)
    {
        int i=0;
		int found=0;
		while(i<table_index && !found)
		{
			if(symbol_table[i].scope==scope && strcmp(symbol_table[i].name,name)==0)
			{
				//printf("warning - line %d : variable redeclared : %s\n",line,name);
                symbol_table[i].line=line;
				strcpy(symbol_table[i].value,value);
				strcpy(symbol_table[i].type,type);
				found=1;
			}
            ++i;
		}
		if(!found)
		{
			make_node(line,name,value,type,scope);
            ++table_index;
		}
    }
    void check_update(int line,char* name,char* value,char* type, int scope)//checks if it exists and update
    {
        int i=0;
		int found=0;
		while(i<table_index && !found)
		{
            if(symbol_table[i].scope<=scope && strcmp(symbol_table[i].name,name)==0)
			{
				symbol_table[i].line=line;
				strcpy(symbol_table[i].value,value);
				strcpy(symbol_table[i].type,type);
				found=1;
			}
            ++i;
        }
        if(!found)
        {
            //printf("line %d : variable undeclared error : %s\n\nParsing failed\n",line,name);
            //exit(0) ;
        }
    }
    void print_table()
    {
        if(table_index==0)
        {   
            printf("\nSymbol table is empty\n");
            return;
        }
        printf("\n\t\t\tSYMBOL TABLE\n\nLine number \t ID name \t Value \t\t Type  \t\t Scope\n");
		for(int i=0;i<table_index;++i)
        {
            printf("%d \t\t %s \t\t %s \t\t %s\t\t %d\n",symbol_table[i].line,symbol_table[i].name,symbol_table[i].value,symbol_table[i].type,symbol_table[i].scope);
        }
    }
    /*char* temporary_update(char* name, int scope)//checks if it exists and update
    {
        int i=0;
		int found=0;
		while(i<table_index && !found)
		{
            if(symbol_table[i].scope<=scope && strcmp(symbol_table[i].name,name)==0)
			{
				
				//printf("temp nu: %s %d %s %s %s\n",temp,line,name, symbol_table[i].value, type);
				return symbol_table[i].value;
			}
            ++i;
        }
        /*if(!found)
        {
            printf("line %d : variable undeclared error : %s\n\nParsing failed\n",line,name);
            exit(0) ;
        }
    }*/
     void temp_add_update_node(char* name,char* value,char* type, int scope)
    {
        int i=0;
		int found=0;
		while(i<table_index && !found)
		{
			if(symbol_table[i].scope==scope && strcmp(symbol_table[i].name,name)==0)
			{
				//printf("warning - line %d : variable redeclared : %s\n",line,name);
                //symbol_table[i].line=line;
				strcpy(symbol_table[i].value,value);
				strcpy(symbol_table[i].type,type);
				found=1;
			}
            ++i;
		}
		if(!found)
		{
			make_temp_node(name,value,type,scope);
            ++table_index;
		}
    }
     void label_add_update_node(char* name, char* value, char* type, int scope)
     {
     	 int i=0;
		int found=0;
		//printf("hi");
		while(i<table_index && !found)
		{
			if(symbol_table[i].scope==scope && strcmp(symbol_table[i].name,name)==0)
			{
				//printf("warning - line %d : variable redeclared : %s\n",line,name);
                //symbol_table[i].line=line;
                //printf("%s",name);
				strcpy(symbol_table[i].value,value);
				strcpy(symbol_table[i].type,type);
				found=1;
			}
            ++i;
		}
		if(!found)
		{
			make_temp_node(name,value,type,scope);
            ++table_index;
		}
     }




#line 287 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_HEADER = 3,                     /* HEADER  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_MAIN = 5,                       /* MAIN  */
  YYSYMBOL_TO = 6,                         /* TO  */
  YYSYMBOL_DOWN_TO = 7,                    /* DOWN_TO  */
  YYSYMBOL_THEN = 8,                       /* THEN  */
  YYSYMBOL_T_lt = 9,                       /* T_lt  */
  YYSYMBOL_T_gt = 10,                      /* T_gt  */
  YYSYMBOL_T_lteq = 11,                    /* T_lteq  */
  YYSYMBOL_T_gteq = 12,                    /* T_gteq  */
  YYSYMBOL_T_neq = 13,                     /* T_neq  */
  YYSYMBOL_T_eqeq = 14,                    /* T_eqeq  */
  YYSYMBOL_T_pl = 15,                      /* T_pl  */
  YYSYMBOL_T_min = 16,                     /* T_min  */
  YYSYMBOL_T_mul = 17,                     /* T_mul  */
  YYSYMBOL_T_div = 18,                     /* T_div  */
  YYSYMBOL_T_and = 19,                     /* T_and  */
  YYSYMBOL_T_or = 20,                      /* T_or  */
  YYSYMBOL_T_incr = 21,                    /* T_incr  */
  YYSYMBOL_T_decr = 22,                    /* T_decr  */
  YYSYMBOL_T_not = 23,                     /* T_not  */
  YYSYMBOL_T_eq = 24,                      /* T_eq  */
  YYSYMBOL_T_assign = 25,                  /* T_assign  */
  YYSYMBOL_T_comma = 26,                   /* T_comma  */
  YYSYMBOL_T_semi = 27,                    /* T_semi  */
  YYSYMBOL_T_dot = 28,                     /* T_dot  */
  YYSYMBOL_T_END = 29,                     /* T_END  */
  YYSYMBOL_INT = 30,                       /* INT  */
  YYSYMBOL_CHAR = 31,                      /* CHAR  */
  YYSYMBOL_FLOAT = 32,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 33,                    /* DOUBLE  */
  YYSYMBOL_VOID = 34,                      /* VOID  */
  YYSYMBOL_BOOL = 35,                      /* BOOL  */
  YYSYMBOL_COUT = 36,                      /* COUT  */
  YYSYMBOL_COUTSTR = 37,                   /* COUTSTR  */
  YYSYMBOL_INS = 38,                       /* INS  */
  YYSYMBOL_CIN = 39,                       /* CIN  */
  YYSYMBOL_XTR = 40,                       /* XTR  */
  YYSYMBOL_IF = 41,                        /* IF  */
  YYSYMBOL_ELSE = 42,                      /* ELSE  */
  YYSYMBOL_DO = 43,                        /* DO  */
  YYSYMBOL_FOR = 44,                       /* FOR  */
  YYSYMBOL_ELSE_IF = 45,                   /* ELSE_IF  */
  YYSYMBOL_T_RETURN = 46,                  /* T_RETURN  */
  YYSYMBOL_ID = 47,                        /* ID  */
  YYSYMBOL_NUM = 48,                       /* NUM  */
  YYSYMBOL_SINGLE_CHAR_VALUE = 49,         /* SINGLE_CHAR_VALUE  */
  YYSYMBOL_OPB = 50,                       /* OPB  */
  YYSYMBOL_CLB = 51,                       /* CLB  */
  YYSYMBOL_OSCOPE = 52,                    /* OSCOPE  */
  YYSYMBOL_CSCOPE = 53,                    /* CSCOPE  */
  YYSYMBOL_54_ = 54,                       /* ':'  */
  YYSYMBOL_55_ = 55,                       /* '('  */
  YYSYMBOL_56_ = 56,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_s = 58,                         /* s  */
  YYSYMBOL_vardefs = 59,                   /* vardefs  */
  YYSYMBOL_var_defs = 60,                  /* var_defs  */
  YYSYMBOL_start = 61,                     /* start  */
  YYSYMBOL_c = 62,                         /* c  */
  YYSYMBOL_empty = 63,                     /* empty  */
  YYSYMBOL_stmt = 64,                      /* stmt  */
  YYSYMBOL_assignment = 65,                /* assignment  */
  YYSYMBOL_66_1 = 66,                      /* $@1  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_expression = 68,                /* expression  */
  YYSYMBOL_69_3 = 69,                      /* $@3  */
  YYSYMBOL_loops = 70,                     /* loops  */
  YYSYMBOL_71_4 = 71,                      /* $@4  */
  YYSYMBOL_72_5 = 72,                      /* $@5  */
  YYSYMBOL_73_6 = 73,                      /* $@6  */
  YYSYMBOL_74_7 = 74,                      /* $@7  */
  YYSYMBOL_75_8 = 75,                      /* $@8  */
  YYSYMBOL_z = 76,                         /* z  */
  YYSYMBOL_77_9 = 77,                      /* $@9  */
  YYSYMBOL_x = 78,                         /* x  */
  YYSYMBOL_79_10 = 79,                     /* $@10  */
  YYSYMBOL_loopbody = 80,                  /* loopbody  */
  YYSYMBOL_cond_stmt = 81,                 /* cond_stmt  */
  YYSYMBOL_cond_stmt_for = 82,             /* cond_stmt_for  */
  YYSYMBOL_cond = 83,                      /* cond  */
  YYSYMBOL_print = 84,                     /* print  */
  YYSYMBOL_read_ip = 85,                   /* read_ip  */
  YYSYMBOL_lit = 86,                       /* lit  */
  YYSYMBOL_TYPE = 87,                      /* TYPE  */
  YYSYMBOL_bin_arop = 88,                  /* bin_arop  */
  YYSYMBOL_bin_boolop = 89,                /* bin_boolop  */
  YYSYMBOL_un_arop = 90,                   /* un_arop  */
  YYSYMBOL_un_boolop = 91,                 /* un_boolop  */
  YYSYMBOL_relop = 92                      /* relop  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   206

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  144

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,    56,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    54,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   226,   226,   229,   231,   234,   236,   239,   240,   241,
     244,   247,   248,   249,   250,   254,   254,   254,   263,   264,
     264,   265,   266,   267,   268,   271,   271,   271,   272,   272,
     272,   274,   274,   278,   278,   279,   282,   282,   283,   284,
     287,   288,   293,   294,   297,   298,   299,   302,   303,   304,
     305,   306,   309,   312,   315,   316,   319,   320,   321,   322,
     323,   326,   327,   328,   329,   332,   333,   336,   337,   340,
     343,   344,   345,   346,   347,   348
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "HEADER", "VAR",
  "MAIN", "TO", "DOWN_TO", "THEN", "T_lt", "T_gt", "T_lteq", "T_gteq",
  "T_neq", "T_eqeq", "T_pl", "T_min", "T_mul", "T_div", "T_and", "T_or",
  "T_incr", "T_decr", "T_not", "T_eq", "T_assign", "T_comma", "T_semi",
  "T_dot", "T_END", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "BOOL",
  "COUT", "COUTSTR", "INS", "CIN", "XTR", "IF", "ELSE", "DO", "FOR",
  "ELSE_IF", "T_RETURN", "ID", "NUM", "SINGLE_CHAR_VALUE", "OPB", "CLB",
  "OSCOPE", "CSCOPE", "':'", "'('", "')'", "$accept", "s", "vardefs",
  "var_defs", "start", "c", "empty", "stmt", "assignment", "$@1", "$@2",
  "expression", "$@3", "loops", "$@4", "$@5", "$@6", "$@7", "$@8", "z",
  "$@9", "x", "$@10", "loopbody", "cond_stmt", "cond_stmt_for", "cond",
  "print", "read_ip", "lit", "TYPE", "bin_arop", "bin_boolop", "un_arop",
  "un_boolop", "relop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    58,    40,    41
};
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-29)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,   -35,    10,   -12,  -117,    30,  -117,   -22,    -4,  -117,
    -117,    -7,    22,   126,  -117,   111,  -117,  -117,  -117,  -117,
      15,    16,    18,   136,    37,  -117,    36,  -117,  -117,  -117,
    -117,  -117,   184,    64,    64,  -117,  -117,  -117,  -117,  -117,
      41,    27,    24,   136,  -117,  -117,    65,  -117,   176,    -3,
      49,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,    64,
    -117,  -117,  -117,  -117,  -117,    39,    40,  -117,    44,  -117,
      70,    88,  -117,  -117,  -117,  -117,  -117,  -117,     2,     2,
     176,  -117,    64,  -117,    71,    72,    89,   136,   136,     7,
      26,     2,    64,  -117,  -117,  -117,  -117,  -117,  -117,     2,
    -117,     2,  -117,  -117,   116,    58,    59,    80,    57,  -117,
      90,    69,   116,   116,     2,  -117,    87,  -117,    82,  -117,
    -117,  -117,  -117,  -117,    91,   136,  -117,    81,  -117,   114,
     116,   -34,   116,    86,  -117,  -117,  -117,   136,    92,  -117,
     121,   116,   -34,  -117
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,    10,     0,     3,     5,
      10,     0,     0,     6,     9,     0,     2,    67,    68,    69,
       0,     0,     0,    10,    54,    55,     0,    11,    12,     8,
      13,    14,    18,     0,     0,    56,    57,    58,    59,    60,
       0,     0,     0,     0,    46,    44,    25,    45,    18,     0,
       0,     7,    61,    62,    63,    64,    65,    66,    19,     0,
      22,    54,    23,    24,     4,     0,     0,    42,     0,    43,
       0,     0,    70,    71,    72,    73,    74,    75,     0,     0,
      18,    16,     0,    21,     0,     0,     0,    10,    10,    47,
       0,     0,     0,    20,    52,    53,    31,    26,    29,     0,
      51,     0,    50,    17,     0,     0,     0,     0,     0,    10,
       0,    10,     0,     0,     0,    49,     0,    41,     0,    35,
      32,    27,    30,    48,     0,     0,    40,     0,    33,     0,
       0,    10,     0,     0,    39,    34,    38,     0,     0,    36,
       0,     0,    10,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -117,  -117,  -117,  -117,  -117,    21,    -6,   -10,  -117,  -117,
    -117,   -17,  -117,  -117,  -117,  -117,  -117,  -117,  -117,  -117,
    -117,    -9,  -117,   -84,  -116,   -29,   -37,  -117,  -117,   -18,
    -117,  -117,    56,   -25,   -21,   -66
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     7,     8,    12,    13,    44,   110,    27,    50,
      92,    28,    82,    29,    70,   105,    71,   106,   104,   120,
     129,   135,   140,   111,    68,    46,    47,    30,    31,    32,
      40,    58,    59,    33,    34,    78
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       9,     1,    49,    26,    14,    48,    69,    60,   132,   127,
       4,   133,     3,    45,    91,     5,    62,    63,    17,    18,
      19,   138,    49,    60,   101,    48,    56,    57,   121,   122,
      10,    80,    63,    67,     6,    72,    73,    74,    75,    76,
      77,   114,    83,    11,    61,    25,   131,    15,   136,    61,
      25,    16,    79,    41,    42,    60,    43,   142,    97,    98,
      89,    90,   -15,    51,    65,    93,    49,    49,    64,    48,
      48,    66,   -28,   102,    81,   103,    87,    45,    45,    84,
      85,   107,   100,   108,    86,    17,    18,    19,    69,    72,
      73,    74,    75,    76,    77,    88,   123,    96,    94,    95,
      69,   112,   113,    14,    49,   119,    26,    48,    17,    18,
      19,    61,    25,   115,   118,    67,    49,   117,   126,    48,
     125,   128,   130,    20,   137,   134,    21,    67,    22,   141,
     116,    23,   139,   143,    24,    25,   134,    17,    18,    19,
     124,    35,    36,    37,    38,    99,    39,    17,    18,    19,
       0,     0,    20,     0,     0,    21,     0,    17,    18,    19,
       0,     0,    20,    24,    25,    21,     0,    22,   109,     0,
      23,     0,    20,    24,    25,    21,     0,     0,     0,     0,
       0,     0,     0,    24,    25,    72,    73,    74,    75,    76,
      77,    52,    53,    54,    55,    56,    57,    17,    18,    52,
      53,    54,    55,    56,    57,    17,    18
};

static const yytype_int16 yycheck[] =
{
       6,     3,    23,    13,    10,    23,    43,    32,    42,   125,
       0,    45,    47,    23,    80,    27,    33,    34,    21,    22,
      23,   137,    43,    48,    90,    43,    19,    20,   112,   113,
      52,    49,    49,    43,     4,     9,    10,    11,    12,    13,
      14,   107,    59,    47,    47,    48,   130,    54,   132,    47,
      48,    29,    55,    38,    38,    80,    38,   141,    87,    88,
      78,    79,    25,    27,    37,    82,    87,    88,    27,    87,
      88,    47,     7,    91,    25,    92,     6,    87,    88,    40,
      40,    99,    56,   101,    40,    21,    22,    23,   125,     9,
      10,    11,    12,    13,    14,     7,   114,     8,    27,    27,
     137,    43,    43,   109,   125,   111,   116,   125,    21,    22,
      23,    47,    48,    56,    45,   125,   137,    27,    27,   137,
      38,    40,     8,    36,    38,   131,    39,   137,    41,     8,
     109,    44,    40,   142,    47,    48,   142,    21,    22,    23,
      53,    30,    31,    32,    33,    89,    35,    21,    22,    23,
      -1,    -1,    36,    -1,    -1,    39,    -1,    21,    22,    23,
      -1,    -1,    36,    47,    48,    39,    -1,    41,    52,    -1,
      44,    -1,    36,    47,    48,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    15,
      16,    17,    18,    19,    20,    21,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    58,    47,     0,    27,     4,    59,    60,    63,
      52,    47,    61,    62,    63,    54,    29,    21,    22,    23,
      36,    39,    41,    44,    47,    48,    64,    65,    68,    70,
      84,    85,    86,    90,    91,    30,    31,    32,    33,    35,
      87,    38,    38,    38,    63,    64,    82,    83,    86,    91,
      66,    27,    15,    16,    17,    18,    19,    20,    88,    89,
      90,    47,    68,    68,    27,    37,    47,    64,    81,    83,
      71,    73,     9,    10,    11,    12,    13,    14,    92,    55,
      86,    25,    69,    68,    40,    40,    40,     6,     7,    86,
      86,    92,    67,    68,    27,    27,     8,    82,    82,    89,
      56,    92,    86,    68,    75,    72,    74,    86,    86,    52,
      64,    80,    43,    43,    92,    56,    62,    27,    45,    63,
      76,    80,    80,    86,    53,    38,    27,    81,    40,    77,
       8,    80,    42,    45,    63,    78,    80,    38,    81,    40,
      79,     8,    80,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    60,    60,    61,    62,    62,    62,
      63,    64,    64,    64,    64,    66,    67,    65,    68,    69,
      68,    68,    68,    68,    68,    71,    72,    70,    73,    74,
      70,    75,    70,    77,    76,    76,    79,    78,    78,    78,
      80,    80,    81,    81,    82,    82,    82,    83,    83,    83,
      83,    83,    84,    85,    86,    86,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    89,    89,    90,    90,    91,
      92,    92,    92,    92,    92,    92
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     2,     5,     1,     1,     3,     2,     1,
       0,     1,     1,     1,     1,     0,     0,     5,     1,     0,
       4,     3,     2,     2,     2,     0,     0,     8,     0,     0,
       8,     0,     8,     0,     8,     1,     0,     8,     2,     1,
       4,     2,     1,     1,     1,     1,     1,     3,     7,     6,
       4,     4,     5,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* var_defs: var_defs ID ':' TYPE T_semi  */
#line 231 "yacc.y"
                                      {
              add_update_node(yylineno,name,"",type,scope);
          }
#line 1635 "y.tab.c"
    break;

  case 15: /* $@1: %empty  */
#line 254 "yacc.y"
              {push_lit(yylval);}
#line 1641 "y.tab.c"
    break;

  case 16: /* $@2: %empty  */
#line 254 "yacc.y"
                                           {push_sign();}
#line 1647 "y.tab.c"
    break;

  case 17: /* assignment: ID $@1 T_assign $@2 expression  */
#line 255 "yacc.y"
          {
              codegen_assign();
              check_update(yylineno,name,value,type,scope);
          }
#line 1656 "y.tab.c"
    break;

  case 19: /* $@3: %empty  */
#line 264 "yacc.y"
                        {push_sign();}
#line 1662 "y.tab.c"
    break;

  case 20: /* expression: lit bin_arop $@3 expression  */
#line 264 "yacc.y"
                                                 {codegen();}
#line 1668 "y.tab.c"
    break;

  case 22: /* expression: lit un_arop  */
#line 266 "yacc.y"
                       {push_sign();codegen_un();}
#line 1674 "y.tab.c"
    break;

  case 25: /* $@4: %empty  */
#line 271 "yacc.y"
                         { for1();}
#line 1680 "y.tab.c"
    break;

  case 26: /* $@5: %empty  */
#line 271 "yacc.y"
                                                    {for3();}
#line 1686 "y.tab.c"
    break;

  case 27: /* loops: FOR cond_stmt_for $@4 TO cond_stmt_for $@5 DO loopbody  */
#line 271 "yacc.y"
                                                                         {for4();}
#line 1692 "y.tab.c"
    break;

  case 28: /* $@6: %empty  */
#line 272 "yacc.y"
                         { for1();}
#line 1698 "y.tab.c"
    break;

  case 29: /* $@7: %empty  */
#line 272 "yacc.y"
                                                         {for3();}
#line 1704 "y.tab.c"
    break;

  case 30: /* loops: FOR cond_stmt_for $@6 DOWN_TO cond_stmt_for $@7 DO loopbody  */
#line 272 "yacc.y"
                                                                              {for4();}
#line 1710 "y.tab.c"
    break;

  case 31: /* $@8: %empty  */
#line 274 "yacc.y"
                                 {if1();}
#line 1716 "y.tab.c"
    break;

  case 32: /* loops: IF INS cond_stmt XTR THEN $@8 loopbody z  */
#line 274 "yacc.y"
                                                     {if3();}
#line 1722 "y.tab.c"
    break;

  case 33: /* $@9: %empty  */
#line 278 "yacc.y"
                            {if2();}
#line 1728 "y.tab.c"
    break;

  case 36: /* $@10: %empty  */
#line 282 "yacc.y"
                            {if2();}
#line 1734 "y.tab.c"
    break;

  case 47: /* cond: lit relop lit  */
#line 302 "yacc.y"
                   {codegen_assigna();}
#line 1740 "y.tab.c"
    break;

  case 54: /* lit: ID  */
#line 315 "yacc.y"
       {push_lit(yylval);}
#line 1746 "y.tab.c"
    break;

  case 55: /* lit: NUM  */
#line 316 "yacc.y"
        {push_lit(value);}
#line 1752 "y.tab.c"
    break;

  case 70: /* relop: T_lt  */
#line 343 "yacc.y"
           {push_sign();}
#line 1758 "y.tab.c"
    break;

  case 71: /* relop: T_gt  */
#line 344 "yacc.y"
           {push_sign();}
#line 1764 "y.tab.c"
    break;

  case 72: /* relop: T_lteq  */
#line 345 "yacc.y"
             {push_sign();}
#line 1770 "y.tab.c"
    break;

  case 73: /* relop: T_gteq  */
#line 346 "yacc.y"
             {push_sign();}
#line 1776 "y.tab.c"
    break;

  case 74: /* relop: T_neq  */
#line 347 "yacc.y"
            {push_sign();}
#line 1782 "y.tab.c"
    break;

  case 75: /* relop: T_eqeq  */
#line 348 "yacc.y"
             {push_sign();}
#line 1788 "y.tab.c"
    break;


#line 1792 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 351 "yacc.y"

#include <stdio.h>
#include <string.h>
#include"lex.yy.c"
#include<ctype.h>
int count=0;
char st[100][100];
char label_node[4];


int main(int argc, char *argv[])
{
	yyin = fopen(argv[1], "r");
	FILE *filePointer;
    printf("THREE ADDRESS CODE\n");
//FILE *filePointer= fopen("input.txt", "w"); 
filePointer = fopen("input.txt", "w");
    if(!yyparse())
    {
		print_table();
        printf("\nParsing complete\n");
         printf("---------------------Quadruples-------------------------\n\n");
    printf("Operator \t Arg1 \t\t Arg2 \t\t Result \n");
    int i;
    for(i=0;i<quadlen;i++)
    {
        printf("%-8s \t %-8s \t %-8s \t %-6s \n",q[i].op,q[i].arg1,q[i].arg2,q[i].res);
        if(q[i].arg1==NULL && q[i].arg2==NULL)
        {
        	fprintf(filePointer, "%s %s %s %s\n", q[i].op,"NULL","NULL",q[i].res);
        }
        else if(q[i].arg1==NULL)
        {
        	fprintf(filePointer, "%s %s %s %s\n", q[i].op,"NULL",q[i].arg2,q[i].res);
        }
        else if(q[i].arg2==NULL)
        {
        	fprintf(filePointer, "%s %s %s %s\n", q[i].op,q[i].arg1,"NULL",q[i].res);
        }	

        else
        {
       		fprintf(filePointer, "%s %s %s %s\n", q[i].op,q[i].arg1,q[i].arg2,q[i].res);
    	}
    }
  }
    
	else
		printf("\nParsing failed\n");
	
	fclose(yyin);
	fclose(filePointer);
    return 0;
}
         
void yyerror(char *s) {
	printf("line %d : %s %s\n", yylineno, s, yytext );
}
void push_lit(char* yy)
{
	strcpy(st[++top],yy);
}

void push_sign()
{
//printf("%s\n",yytext);
strcpy(st[++top],yytext);
}
void codegen_assign()
{
    /*for(int i=top;i>=0;i--)
    {
    	printf("%s",st[i]);
    }*/
    printf("%s = %s\n",st[top-2],st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    strcpy(q[quadlen].op,"=");
    strcpy(q[quadlen].arg1,st[top]);
    strcpy(q[quadlen].res,st[top-2]);
    quadlen++;
    top=-1;
}
void codegen_un()
{
    //printf("hi");
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    //printf("temporaries\n");
    temp_add_update_node(temp, "-", "temp",scope);
     //void add_update_node(int line,char* name,char* value,char* type, int scope)
     //char st_t=st[top][0];
     char* add="1";
     char* st_op;
     //printf("op%s",st[top]);
     if(strcmp(st[top],"++")==0)
     {
     	st_op="+";
     }
     else if(strcmp(st[top],"--")==0)
     {
     	st_op="-";
     }
    printf("%s =  %s %s %s\n",temp,st[top-1],st_op,add);//creating temp=i+1
    q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st_op));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(add));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    //printf("%s",st[top-2]);
    strcpy(q[quadlen].op,st_op);
    strcpy(q[quadlen].arg1,st[top-1]);
    strcpy(q[quadlen].arg2,add);
    strcpy(q[quadlen].res,temp);
    quadlen++;
    printf("%s = %s\n", st[top-1],temp);
     q[quadlen].op = (char*)malloc(sizeof(char)*strlen("="));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    strcpy(q[quadlen].op,"=");
    strcpy(q[quadlen].arg1,temp);
    strcpy(q[quadlen].res,st[top-1]);
    quadlen++;
    top-=2;
    strcpy(st[top],temp);
    temp_i++;
    //printf("%s = %s\n", st[top-1],temp);
    
    
    /*q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    //char* value_1=temporary_update( q[quadlen].arg1,scope);
    //printf("value 1: %s\n",value_1);
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top[0]]));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    
    strcpy(q[quadlen].op,st[top-1]);
    strcpy(q[quadlen].arg1,st[top-2]);
    strcpy(q[quadlen].arg2,st[top]);
    strcpy(q[quadlen].res,temp);
    //printf("temporaries");
    quadlen++;
    top-=2;
    strcpy(st[top],temp);

temp_i++;*/
}
void codegen()
{
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    //printf("temporaries\n");
    temp_add_update_node(temp, "-", "temp",scope);
     //void add_update_node(int line,char* name,char* value,char* type, int scope)
    printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    //char* value_1=temporary_update( q[quadlen].arg1,scope);
    //printf("value 1: %s\n",value_1);
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    
    strcpy(q[quadlen].op,st[top-1]);
    strcpy(q[quadlen].arg1,st[top-2]);
    strcpy(q[quadlen].arg2,st[top]);
    strcpy(q[quadlen].res,temp);
    //printf("temporaries");
    quadlen++;
    top-=2;
    strcpy(st[top],temp);

temp_i++;
}
/*void return_code()//for the if clause
{
	//printf("here");
 lnum++;
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temp",scope);
 printf("%s = not %s\n",temp,st[top]);
 q[quadlen].op = (char*)malloc(sizeof(char)*4);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
 strcpy(q[quadlen].op,"not");
 strcpy(q[quadlen].arg1,st[top]);
 strcpy(q[quadlen].res,temp);
 quadlen++;
 printf("if %s goto L%d\n",temp,lnum);
 q[quadlen].op = (char*)malloc(sizeof(char)*3);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
 strcpy(q[quadlen].op,"if");
 strcpy(q[quadlen].arg1,temp);
 char x[10];
 sprintf(x,"%d",lnum);
 char l[]="L";
 strcpy(q[quadlen].res,strcat(l,x));
 quadlen++;

 temp_i++;
 label[++ltop]=lnum;
}*/

void if1()//for the if clause
{
	//printf("here");
 lnum++;
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temp",scope);
 printf("%s = not %s\n",temp,st[top]);
 q[quadlen].op = (char*)malloc(sizeof(char)*4);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
 strcpy(q[quadlen].op,"not");
 strcpy(q[quadlen].arg1,st[top]);
 strcpy(q[quadlen].res,temp);
 quadlen++;
 printf("if %s goto L%d\n",temp,lnum);
 q[quadlen].op = (char*)malloc(sizeof(char)*3);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
 strcpy(q[quadlen].op,"if");
 strcpy(q[quadlen].arg1,temp);
 char x[10];
 sprintf(x,"%d",lnum);
 char l[]="L";
 strcpy(q[quadlen].res,strcat(l,x));
 //printf("HI");
 label_add_update_node(q[quadlen].res, "-", "label",scope);
 quadlen++;

 temp_i++;
 label[++ltop]=lnum;
    

}
void if2()
{
int y=label[ltop--];
 printf("L%d: \n",y);
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temp",scope);
 printf("%s = not %s\n",temp,st[top]);
 q[quadlen].op = (char*)malloc(sizeof(char)*4);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
 strcpy(q[quadlen].op,"not");
 strcpy(q[quadlen].arg1,st[top]);
 strcpy(q[quadlen].res,temp);
 quadlen++;
 printf("if %s goto L%d\n",temp,lnum);
 q[quadlen].op = (char*)malloc(sizeof(char)*3);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
 strcpy(q[quadlen].op,"if");
 strcpy(q[quadlen].arg1,temp);
 char x[10];
 sprintf(x,"%d",lnum);
 char l[]="L";
 strcpy(q[quadlen].res,strcat(l,x));
 //printf("HI");
 label_add_update_node(q[quadlen].res, "-", "label",scope);
 quadlen++;
	
 temp_i++;
 label[++ltop]=lnum;
}

void codegen_assigna()//for  conditions
{
	strcpy(temp,"T");
	sprintf(tmp_i, "%d", temp_i);
	strcat(temp,tmp_i);
	temp_add_update_node(temp, "-", "temp",scope);
	printf("%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
	//printf("%d\n",strlen(st[top]));
	//if(strlen(st[top])==1)
	if(1)
	{
		//printf("hello");
	
    	char t[20];
		//printf("hello");
		strcpy(t,st[top-1]);
		//strcat(t,st[top-1]);
		q[quadlen].op = (char*)malloc(sizeof(char)*strlen(t));
    	q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-3]));
    	q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top]));
    	q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    	strcpy(q[quadlen].op,t);
    	strcpy(q[quadlen].arg1,st[top-2]);
    	strcpy(q[quadlen].arg2,st[top]);
    	strcpy(q[quadlen].res,temp);
    	quadlen++;
    
	}
	else
	{
		q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    	q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-3]));
    	q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    	q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    	strcpy(q[quadlen].op,st[top-2]);
    	strcpy(q[quadlen].arg1,st[top-3]);
    	strcpy(q[quadlen].arg2,st[top-1]);
    	strcpy(q[quadlen].res,temp);
    	quadlen++;
	}
	top-=4;

	temp_i++;
	strcpy(st[++top],temp);
}
void if3()//after if clause body
{
    int y;
    y=label[ltop--];
    printf("L%d: \n",y);
    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(y+2));
    strcpy(q[quadlen].op,"Label");
    char x[10];
    sprintf(x,"%d",y);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,x));
    quadlen++;
}


void for1()
{
    l_for = lnum;
    printf("L%d: \n",lnum++);
    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"Label");
    char x[10];
    sprintf(x,"%d",lnum-1);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,x));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;
}
void for2()
{
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    temp_add_update_node(temp, "-", "temp",scope);
    printf("%s = not %s\n",temp,st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char)*4);
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    strcpy(q[quadlen].op,"not");
    strcpy(q[quadlen].arg1,st[top]);
    strcpy(q[quadlen].res,temp);
    quadlen++;
    //printf("hi");
    printf("if %s goto L%d\n",temp,lnum);
    //printf("hi");
    q[quadlen].op = (char*)malloc(sizeof(char)*2);
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"if");
    strcpy(q[quadlen].arg1,temp);
    char x[10];
    sprintf(x,"%d",lnum);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,x));
    label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;//after this it creates a node in quadruples for if
    temp_i++;
    label[++ltop]=lnum;
    sprintf(label_node, "%d", lnum);
    lnum++;
    printf("goto L%d\n",lnum);
    q[quadlen].op = (char*)malloc(sizeof(char)*5);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"goto");
    char x1[10];
    sprintf(x1,"%d",lnum);
    char l1[]="L";
    strcpy(q[quadlen].res,strcat(l1,x1));
    quadlen++;
    label[++ltop]=lnum;
    sprintf(label_node, "%d", lnum);
    printf("L%d: \n",++lnum);
    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"Label");
    char x2[10];
    sprintf(x2,"%d",lnum);
    char l2[]="L";
    strcpy(q[quadlen].res,strcat(l2,x2));
    quadlen++;
    

 }
void for3()
{
    int x;
    x=label[ltop--];
    printf("goto L%d \n",l_for);

    q[quadlen].op = (char*)malloc(sizeof(char)*5);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    strcpy(q[quadlen].op,"goto");
    char jug[10];
    sprintf(jug,"%d",l_for);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,jug));
    quadlen++;

    printf("L%d: \n",x);

    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(x+2));
    strcpy(q[quadlen].op,"Label");
    char jug1[10];
    sprintf(jug1,"%d",x);
    char l1[]="L";
    strcpy(q[quadlen].res,strcat(l1,jug1));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;

}

void for4()
{
    int x;
    x=label[ltop--];
    printf("goto L%d \n",lnum);

    q[quadlen].op = (char*)malloc(sizeof(char)*5);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    strcpy(q[quadlen].op,"goto");
    char jug[10];
    sprintf(jug,"%d",lnum);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,jug));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;

    printf("L%d: \n",x);

    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(x+2));
    strcpy(q[quadlen].op,"Label");
    char jug1[10];
    sprintf(jug1,"%d",x);
    char l1[]="L";
    strcpy(q[quadlen].res,strcat(l1,jug1));
    quadlen++;
}
