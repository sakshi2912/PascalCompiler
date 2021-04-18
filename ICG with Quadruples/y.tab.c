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
int l_while=0;
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
				//printf("\twarning - line %d : variable redeclared : %s\n",line,name);
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
            printf("\tline %d : variable undeclared error : %s\n\n Skipping \n",line,name);
            //exit(0) ;
        }
    }
    void print_table()
    {
        if(table_index==0)
        {   
            printf("\t\nSymbol table is empty\n");
            return;
        }
        printf("\t-----------------------------------SYMBOL TABLE-----------------------------------\n\n\tLine number \t ID name \t Value \t\t Type  \t\t Scope\n");
		for(int i=0;i<table_index;++i)
        {
            printf("\t%d \t\t %s \t\t %s \t\t %s\t\t %d\n",symbol_table[i].line,symbol_table[i].name,symbol_table[i].value,symbol_table[i].type,symbol_table[i].scope);
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
				
				//printf("\ttemp nu: %s %d %s %s %s\n",temp,line,name, symbol_table[i].value, type);
				return symbol_table[i].value;
			}
            ++i;
        }
        /*if(!found)
        {
            printf("\tline %d : variable undeclared error : %s\n\nParsing failed\n",line,name);
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
				//printf("\twarning - line %d : variable redeclared : %s\n",line,name);
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
		//printf("\thi");
		while(i<table_index && !found)
		{
			if(symbol_table[i].scope==scope && strcmp(symbol_table[i].name,name)==0)
			{
				//printf("\twarning - line %d : variable redeclared : %s\n",line,name);
                //symbol_table[i].line=line;
                //printf("\t%s",name);
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




#line 288 "y.tab.c"

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
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_INT = 31,                       /* INT  */
  YYSYMBOL_CHAR = 32,                      /* CHAR  */
  YYSYMBOL_FLOAT = 33,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 34,                    /* DOUBLE  */
  YYSYMBOL_VOID = 35,                      /* VOID  */
  YYSYMBOL_BOOL = 36,                      /* BOOL  */
  YYSYMBOL_COUT = 37,                      /* COUT  */
  YYSYMBOL_COUTSTR = 38,                   /* COUTSTR  */
  YYSYMBOL_INS = 39,                       /* INS  */
  YYSYMBOL_CIN = 40,                       /* CIN  */
  YYSYMBOL_XTR = 41,                       /* XTR  */
  YYSYMBOL_IF = 42,                        /* IF  */
  YYSYMBOL_ELSE = 43,                      /* ELSE  */
  YYSYMBOL_DO = 44,                        /* DO  */
  YYSYMBOL_FOR = 45,                       /* FOR  */
  YYSYMBOL_ELSE_IF = 46,                   /* ELSE_IF  */
  YYSYMBOL_T_RETURN = 47,                  /* T_RETURN  */
  YYSYMBOL_ID = 48,                        /* ID  */
  YYSYMBOL_NUM = 49,                       /* NUM  */
  YYSYMBOL_SINGLE_CHAR_VALUE = 50,         /* SINGLE_CHAR_VALUE  */
  YYSYMBOL_OPB = 51,                       /* OPB  */
  YYSYMBOL_CLB = 52,                       /* CLB  */
  YYSYMBOL_OSCOPE = 53,                    /* OSCOPE  */
  YYSYMBOL_CSCOPE = 54,                    /* CSCOPE  */
  YYSYMBOL_55_ = 55,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_s = 57,                         /* s  */
  YYSYMBOL_vardefs = 58,                   /* vardefs  */
  YYSYMBOL_var_defs = 59,                  /* var_defs  */
  YYSYMBOL_start = 60,                     /* start  */
  YYSYMBOL_c = 61,                         /* c  */
  YYSYMBOL_empty = 62,                     /* empty  */
  YYSYMBOL_stmt = 63,                      /* stmt  */
  YYSYMBOL_assignment = 64,                /* assignment  */
  YYSYMBOL_65_1 = 65,                      /* $@1  */
  YYSYMBOL_66_2 = 66,                      /* $@2  */
  YYSYMBOL_expression = 67,                /* expression  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_loops = 69,                     /* loops  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_72_6 = 72,                      /* $@6  */
  YYSYMBOL_z = 73,                         /* z  */
  YYSYMBOL_74_7 = 74,                      /* $@7  */
  YYSYMBOL_x = 75,                         /* x  */
  YYSYMBOL_76_8 = 76,                      /* $@8  */
  YYSYMBOL_loopbody = 77,                  /* loopbody  */
  YYSYMBOL_cond_stmt = 78,                 /* cond_stmt  */
  YYSYMBOL_cond = 79,                      /* cond  */
  YYSYMBOL_print = 80,                     /* print  */
  YYSYMBOL_read_ip = 81,                   /* read_ip  */
  YYSYMBOL_lit = 82,                       /* lit  */
  YYSYMBOL_TYPE = 83,                      /* TYPE  */
  YYSYMBOL_bin_arop = 84,                  /* bin_arop  */
  YYSYMBOL_bin_boolop = 85,                /* bin_boolop  */
  YYSYMBOL_un_arop = 86,                   /* un_arop  */
  YYSYMBOL_un_boolop = 87,                 /* un_boolop  */
  YYSYMBOL_relop = 88                      /* relop  */
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   180

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  134

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   309


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    55,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   227,   227,   228,   235,   237,   240,   242,   245,   246,
     247,   250,   253,   254,   255,   256,   259,   259,   259,   268,
     269,   269,   270,   271,   272,   273,   276,   276,   276,   277,
     277,   278,   282,   282,   285,   285,   286,   289,   290,   295,
     296,   304,   305,   306,   307,   308,   311,   314,   317,   318,
     321,   322,   323,   324,   325,   328,   329,   330,   331,   334,
     335,   338,   339,   342,   345,   346,   347,   348,   349,   350
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
  "T_dot", "T_END", "WHILE", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID",
  "BOOL", "COUT", "COUTSTR", "INS", "CIN", "XTR", "IF", "ELSE", "DO",
  "FOR", "ELSE_IF", "T_RETURN", "ID", "NUM", "SINGLE_CHAR_VALUE", "OPB",
  "CLB", "OSCOPE", "CSCOPE", "':'", "$accept", "s", "vardefs", "var_defs",
  "start", "c", "empty", "stmt", "assignment", "$@1", "$@2", "expression",
  "$@3", "loops", "$@4", "$@5", "$@6", "z", "$@7", "x", "$@8", "loopbody",
  "cond_stmt", "cond", "print", "read_ip", "lit", "TYPE", "bin_arop",
  "bin_boolop", "un_arop", "un_boolop", "relop", YY_NULLPTR
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
     305,   306,   307,   308,   309,    58
};
#endif

#define YYPACT_NINF (-96)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      21,   -96,   -42,    11,     0,   -96,    31,   -96,   -22,   -11,
     -96,   -96,    -4,    12,    87,   -96,   119,   -96,   -96,   -96,
     -96,   -96,    10,    13,    14,    32,   -96,   -96,    34,   -96,
     -96,   -96,   -96,   -96,   158,   109,   109,   -96,   -96,   -96,
     -96,   -96,    35,    19,    25,    16,   100,    40,   -96,   -96,
     -96,   -96,   -96,   -96,   -96,   -96,   109,   -96,   -96,   -96,
     -96,   -96,   100,    30,    33,   -96,    36,   -96,   150,    57,
     -96,   109,   -96,    50,    49,    54,    78,   -96,   -96,   -96,
     -96,   -96,   -96,   -15,   -15,   150,   109,   -96,   -96,   -96,
     -96,   -96,    27,     3,   -15,   -96,    48,    67,   -15,   -96,
     -15,   -96,    67,   -96,    70,    52,   132,    59,   -96,    45,
     -96,    62,   -96,   -15,   -96,   -96,   100,   -96,    71,   -96,
     103,    67,   -23,    67,    75,   -96,   -96,   100,    77,   -96,
     111,    67,   -23,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     3,     0,     0,     0,     1,     0,    11,     0,     4,
       6,    11,     0,     0,     7,    10,     0,     2,    61,    62,
      63,    26,     0,     0,     0,    48,    49,    31,     0,    12,
      13,     9,    14,    15,    19,     0,     0,    50,    51,    52,
      53,    54,     0,     0,     0,     0,     0,     0,     8,    55,
      56,    57,    58,    59,    60,    20,     0,    23,    48,    24,
      25,     5,     0,     0,     0,    39,     0,    40,    19,     0,
      17,     0,    22,     0,     0,     0,     0,    64,    65,    66,
      67,    68,    69,     0,     0,    19,     0,    21,    27,    46,
      47,    29,    41,     0,     0,    18,     0,     0,     0,    45,
       0,    44,     0,    11,     0,     0,     0,     0,    28,     0,
      38,     0,    30,     0,    43,    37,     0,    42,     0,    32,
       0,     0,     0,     0,     0,    33,    36,     0,     0,    34,
       0,     0,     0,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -96,   -96,   -96,   -96,   -96,    22,    -6,   -14,   -96,   -96,
     -96,   -26,   -96,   -96,   -96,   -96,   -96,   -96,   -96,     1,
     -96,   -95,   -57,   -96,   -96,   -96,   -44,   -96,   -96,    42,
     -30,   -43,   -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     8,     9,    13,    14,    15,   104,    29,    47,
      86,    30,    71,    31,    43,    96,    97,   112,   120,   125,
     130,   105,    66,    67,    32,    33,    34,    42,    55,    56,
      35,    36,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    10,    68,    69,    57,    73,     4,   108,    27,    59,
      60,     5,    77,    78,    79,    80,    81,    82,    68,    69,
     123,    94,     1,   124,     2,    85,   122,     6,   126,   100,
      72,    11,    65,    58,    26,     7,   132,    12,    57,    92,
      93,    17,   113,    60,    99,    87,    53,    54,    65,    44,
     101,    16,    45,    46,   106,    57,   107,   -16,    62,   118,
      95,    48,    61,    63,    64,    70,    18,    19,    20,   117,
     128,    74,    68,    69,    75,    21,    89,    76,    18,    19,
      20,    90,    22,    68,    69,    23,    91,    24,    18,    19,
      20,    88,   102,    25,    26,    28,    84,   110,   111,   115,
     114,   116,    65,    27,    22,    58,    26,    23,    18,    19,
      20,   121,   119,    65,   127,    25,    26,    21,   129,   131,
     103,    18,    19,    20,    22,   109,     0,    23,     0,    24,
      18,    19,    20,   133,    98,    25,    26,    22,     0,     0,
      23,    77,    78,    79,    80,    81,    82,     0,    25,    26,
      37,    38,    39,    40,     0,    41,     0,    58,    26,    77,
      78,    79,    80,    81,    82,    49,    50,    51,    52,    53,
      54,    18,    19,    49,    50,    51,    52,    53,    54,    18,
      19
};

static const yytype_int16 yycheck[] =
{
      14,     7,    46,    46,    34,    62,    48,   102,    14,    35,
      36,     0,     9,    10,    11,    12,    13,    14,    62,    62,
      43,    85,     1,    46,     3,    69,   121,    27,   123,    93,
      56,    53,    46,    48,    49,     4,   131,    48,    68,    83,
      84,    29,   106,    69,    41,    71,    19,    20,    62,    39,
      94,    55,    39,    39,    98,    85,   100,    25,    39,   116,
      86,    27,    27,    38,    48,    25,    21,    22,    23,   113,
     127,    41,   116,   116,    41,    30,    27,    41,    21,    22,
      23,    27,    37,   127,   127,    40,     8,    42,    21,    22,
      23,    41,    44,    48,    49,   109,    39,    27,    46,    54,
      41,    39,   116,   109,    37,    48,    49,    40,    21,    22,
      23,     8,    41,   127,    39,    48,    49,    30,    41,     8,
      53,    21,    22,    23,    37,   103,    -1,    40,    -1,    42,
      21,    22,    23,   132,    92,    48,    49,    37,    -1,    -1,
      40,     9,    10,    11,    12,    13,    14,    -1,    48,    49,
      31,    32,    33,    34,    -1,    36,    -1,    48,    49,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    15,    16,    17,    18,    19,    20,    21,
      22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    57,    48,     0,    27,     4,    58,    59,
      62,    53,    48,    60,    61,    62,    55,    29,    21,    22,
      23,    30,    37,    40,    42,    48,    49,    62,    63,    64,
      67,    69,    80,    81,    82,    86,    87,    31,    32,    33,
      34,    36,    83,    70,    39,    39,    39,    65,    27,    15,
      16,    17,    18,    19,    20,    84,    85,    86,    48,    67,
      67,    27,    39,    38,    48,    63,    78,    79,    82,    87,
      25,    68,    67,    78,    41,    41,    41,     9,    10,    11,
      12,    13,    14,    88,    39,    82,    66,    67,    41,    27,
      27,     8,    82,    82,    88,    67,    71,    72,    85,    41,
      88,    82,    44,    53,    63,    77,    82,    82,    77,    61,
      27,    46,    73,    88,    41,    54,    39,    82,    78,    41,
      74,     8,    77,    43,    46,    75,    77,    39,    78,    41,
      76,     8,    77,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    57,    58,    59,    59,    60,    61,    61,
      61,    62,    63,    63,    63,    63,    65,    66,    64,    67,
      68,    67,    67,    67,    67,    67,    70,    71,    69,    72,
      69,    69,    74,    73,    76,    75,    75,    77,    77,    78,
      78,    79,    79,    79,    79,    79,    80,    81,    82,    82,
      83,    83,    83,    83,    83,    84,    84,    84,    84,    85,
      85,    86,    86,    87,    88,    88,    88,    88,    88,    88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     1,     2,     5,     1,     1,     3,     2,
       1,     0,     1,     1,     1,     1,     0,     0,     5,     1,
       0,     4,     3,     2,     2,     2,     0,     0,     8,     0,
       8,     1,     0,     8,     0,     8,     2,     3,     2,     1,
       1,     3,     7,     6,     4,     4,     5,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1
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
  case 3: /* s: error  */
#line 228 "yacc.y"
          {
           
            yyerrok;
            yyclearin;
            }
#line 1625 "y.tab.c"
    break;

  case 5: /* var_defs: var_defs ID ':' TYPE T_semi  */
#line 237 "yacc.y"
                                      {
              add_update_node(yylineno,name,"",type,scope);
          }
#line 1633 "y.tab.c"
    break;

  case 13: /* stmt: expression  */
#line 254 "yacc.y"
                {yyval=yyvsp[0];}
#line 1639 "y.tab.c"
    break;

  case 16: /* $@1: %empty  */
#line 259 "yacc.y"
              {push_lit(yylval);}
#line 1645 "y.tab.c"
    break;

  case 17: /* $@2: %empty  */
#line 259 "yacc.y"
                                           {push_sign();}
#line 1651 "y.tab.c"
    break;

  case 18: /* assignment: ID $@1 T_assign $@2 expression  */
#line 260 "yacc.y"
          {
              codegen_assign();
              check_update(yylineno,name,value,type,scope);
          }
#line 1660 "y.tab.c"
    break;

  case 19: /* expression: lit  */
#line 268 "yacc.y"
               {yyval=yyvsp[0];}
#line 1666 "y.tab.c"
    break;

  case 20: /* $@3: %empty  */
#line 269 "yacc.y"
                        {push_sign();}
#line 1672 "y.tab.c"
    break;

  case 21: /* expression: lit bin_arop $@3 expression  */
#line 269 "yacc.y"
                                                 {codegen();}
#line 1678 "y.tab.c"
    break;

  case 23: /* expression: lit un_arop  */
#line 271 "yacc.y"
                       {push_sign();codegen_un();}
#line 1684 "y.tab.c"
    break;

  case 26: /* $@4: %empty  */
#line 276 "yacc.y"
            {while1();}
#line 1690 "y.tab.c"
    break;

  case 27: /* $@5: %empty  */
#line 276 "yacc.y"
                                          {while2();}
#line 1696 "y.tab.c"
    break;

  case 28: /* loops: WHILE $@4 INS cond_stmt XTR $@5 DO loopbody  */
#line 276 "yacc.y"
                                                                  {while3();}
#line 1702 "y.tab.c"
    break;

  case 29: /* $@6: %empty  */
#line 277 "yacc.y"
                                 {if1();}
#line 1708 "y.tab.c"
    break;

  case 30: /* loops: IF INS cond_stmt XTR THEN $@6 loopbody z  */
#line 277 "yacc.y"
                                                     {if3();}
#line 1714 "y.tab.c"
    break;

  case 32: /* $@7: %empty  */
#line 282 "yacc.y"
                            {if2();}
#line 1720 "y.tab.c"
    break;

  case 34: /* $@8: %empty  */
#line 285 "yacc.y"
                            {if2();}
#line 1726 "y.tab.c"
    break;

  case 41: /* cond: lit relop lit  */
#line 304 "yacc.y"
                   {codegen_assigna();}
#line 1732 "y.tab.c"
    break;

  case 48: /* lit: ID  */
#line 317 "yacc.y"
       {push_lit(yylval);}
#line 1738 "y.tab.c"
    break;

  case 49: /* lit: NUM  */
#line 318 "yacc.y"
        {push_lit(value);}
#line 1744 "y.tab.c"
    break;

  case 64: /* relop: T_lt  */
#line 345 "yacc.y"
           {push_sign();}
#line 1750 "y.tab.c"
    break;

  case 65: /* relop: T_gt  */
#line 346 "yacc.y"
           {push_sign();}
#line 1756 "y.tab.c"
    break;

  case 66: /* relop: T_lteq  */
#line 347 "yacc.y"
             {push_sign();}
#line 1762 "y.tab.c"
    break;

  case 67: /* relop: T_gteq  */
#line 348 "yacc.y"
             {push_sign();}
#line 1768 "y.tab.c"
    break;

  case 68: /* relop: T_neq  */
#line 349 "yacc.y"
            {push_sign();}
#line 1774 "y.tab.c"
    break;

  case 69: /* relop: T_eqeq  */
#line 350 "yacc.y"
             {push_sign();}
#line 1780 "y.tab.c"
    break;


#line 1784 "y.tab.c"

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

#line 353 "yacc.y"

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
    printf("\n\t---------------------THREE ADDRESS CODE---------------------\n\n");
//FILE *filePointer= fopen("input.txt", "w"); 
filePointer = fopen("input.txt", "w");
    if(!yyparse())
    {
		print_table();
        printf("\n\n\tParsing complete\n\n\n");
         printf("\t---------------------Quadruples-------------------------\n\n");
    printf("\n\tOperator \t Arg1 \t\t Arg2 \t\t Result \n");
    int i;
    for(i=0;i<quadlen;i++)
    {
        printf("\t%-8s \t %-8s \t %-8s \t %-6s \n",q[i].op,q[i].arg1,q[i].arg2,q[i].res);
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
		printf("\t\nParsing failed\n");
	
	fclose(yyin);
	fclose(filePointer);
    return 0;
}
         
void yyerror(char *s) {
	printf("\tline %d : %s %s\n", yylineno, s, yytext );
}
void push_lit(char* yy)
{
	strcpy(st[++top],yy);
}

void push_sign()
{
//printf("\t%s\n",yytext);
strcpy(st[++top],yytext);
}
void codegen_assign()
{
    /*for(int i=top;i>=0;i--)
    {
    	printf("\t%s",st[i]);
    }*/
    printf("\t%s = %s\n",st[top-2],st[top]);
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
    //printf("\thi");
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    //printf("\ttemporaries\n");
    temp_add_update_node(temp, "-", "temp",scope);
     //void add_update_node(int line,char* name,char* value,char* type, int scope)
     //char st_t=st[top][0];
     char* add="1";
     char* st_op;
     //printf("\top%s",st[top]);
     if(strcmp(st[top],"++")==0)
     {
     	st_op="+";
     }
     else if(strcmp(st[top],"--")==0)
     {
     	st_op="-";
     }
    printf("\t%s =  %s %s %s\n",temp,st[top-1],st_op,add);//creating temp=i+1
    q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st_op));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(add));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    //printf("\t%s",st[top-2]);
    strcpy(q[quadlen].op,st_op);
    strcpy(q[quadlen].arg1,st[top-1]);
    strcpy(q[quadlen].arg2,add);
    strcpy(q[quadlen].res,temp);
    quadlen++;
    printf("\t%s = %s\n", st[top-1],temp);
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
    //printf("\t%s = %s\n", st[top-1],temp);
    
    
    /*q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    //char* value_1=temporary_update( q[quadlen].arg1,scope);
    //printf("\tvalue 1: %s\n",value_1);
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top[0]]));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    
    strcpy(q[quadlen].op,st[top-1]);
    strcpy(q[quadlen].arg1,st[top-2]);
    strcpy(q[quadlen].arg2,st[top]);
    strcpy(q[quadlen].res,temp);
    //printf("\ttemporaries");
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
    //printf("\ttemporaries\n");
    temp_add_update_node(temp, "-", "temp",scope);
     //void add_update_node(int line,char* name,char* value,char* type, int scope)
    printf("\t%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char)*strlen(st[top-1]));
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top-2]));
    //char* value_1=temporary_update( q[quadlen].arg1,scope);
    //printf("\tvalue 1: %s\n",value_1);
    q[quadlen].arg2 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    
    strcpy(q[quadlen].op,st[top-1]);
    strcpy(q[quadlen].arg1,st[top-2]);
    strcpy(q[quadlen].arg2,st[top]);
    strcpy(q[quadlen].res,temp);
    //printf("\ttemporaries");
    quadlen++;
    top-=2;
    strcpy(st[top],temp);

temp_i++;
}
void while1()
{

    l_while = lnum;
    printf("\tL%d : \n",lnum++);
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

void while2()
{
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temporary",scope);
 printf("\t%s = not %s\n",temp,st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char)*4);
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    strcpy(q[quadlen].op,"not");
    strcpy(q[quadlen].arg1,st[top]);
    strcpy(q[quadlen].res,temp);
    quadlen++;
    printf("\tif %s goto L%d\n",temp,lnum);
    q[quadlen].op = (char*)malloc(sizeof(char)*3);
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(temp));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"if");
    strcpy(q[quadlen].arg1,temp);
    char x[10];
    sprintf(x,"%d",lnum);char l[]="L";
    strcpy(q[quadlen].res,strcat(l,x));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;

 temp_i++;
 }

void while3()
{

printf("\tgoto L%d \n",l_while);
q[quadlen].op = (char*)malloc(sizeof(char)*5);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(l_while+2));
    strcpy(q[quadlen].op,"goto");
    char x[10];
    sprintf(x,"%d",l_while);
    char l[]="L";
    strcpy(q[quadlen].res,strcat(l,x));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;
    printf("\tL%d : \n",lnum++);
    q[quadlen].op = (char*)malloc(sizeof(char)*6);
    q[quadlen].arg1 = NULL;
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*(lnum+2));
    strcpy(q[quadlen].op,"Label");
    char x1[10];
    sprintf(x1,"%d",lnum-1);
    char l1[]="L";
    strcpy(q[quadlen].res,strcat(l1,x1));
     label_add_update_node(q[quadlen].res, "-", "label",scope);
    quadlen++;
}


void if1()//for the if clause
{
	//printf("\there");
 lnum++;
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temp",scope);
 printf("\t%s = not %s\n",temp,st[top]);
 q[quadlen].op = (char*)malloc(sizeof(char)*4);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
 strcpy(q[quadlen].op,"not");
 strcpy(q[quadlen].arg1,st[top]);
 strcpy(q[quadlen].res,temp);
 quadlen++;
 printf("\tif %s goto L%d\n",temp,lnum);
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
 //printf("\tHI");
 label_add_update_node(q[quadlen].res, "-", "label",scope);
 quadlen++;

 temp_i++;
 label[++ltop]=lnum;
    

}
void if2()
{
int y=label[ltop--];
 printf("\tL%d : \n",y);
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_add_update_node(temp, "-", "temp",scope);
 printf("\t%s = not %s\n",temp,st[top]);
 q[quadlen].op = (char*)malloc(sizeof(char)*4);
 q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
 q[quadlen].arg2 = NULL;
 q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
 strcpy(q[quadlen].op,"not");
 strcpy(q[quadlen].arg1,st[top]);
 strcpy(q[quadlen].res,temp);
 quadlen++;
 printf("\tif %s goto L%d\n",temp,lnum);
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
 //printf("\tHI");
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
	printf("\t%s = %s %s %s\n",temp,st[top-2],st[top-1],st[top]);
	//printf("\t%d\n",strlen(st[top]));
	//if(strlen(st[top])==1)
	if(1)
	{
		//printf("\thello");
	
    	char t[20];
		//printf("\thello");
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
    printf("\tL%d : \n",y);
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
