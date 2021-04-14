%{
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
            //printf("\tline %d : variable undeclared error : %s\n\nParsing failed\n",line,name);
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



%}

%token HEADER VAR MAIN TO DOWN_TO THEN
%token T_lt T_gt T_lteq T_gteq T_neq T_eqeq T_pl T_min T_mul T_div T_and T_or T_incr T_decr T_not T_eq T_assign T_comma T_semi T_dot T_END
%token INT CHAR FLOAT DOUBLE VOID BOOL COUT COUTSTR INS CIN XTR
%token IF ELSE DO FOR ELSE_IF T_RETURN
%token ID NUM SINGLE_CHAR_VALUE
%token OPB CLB OSCOPE CSCOPE

%%

s:HEADER ID  T_semi vardefs OSCOPE start T_END
 | error  {
           
            yyerrok;
            yyclearin;
            };
 ;

vardefs: VAR  var_defs ;

var_defs: var_defs ID ':' TYPE  T_semi{
              add_update_node(yylineno,name,"",type,scope);
          };
          | empty;
          
start:c
     ;

c:c stmt T_semi
 |c loops
 |empty
 ;

empty:
     ;

stmt:assignment
    |expression
    |print
    |read_ip
    //| T_RETURN expression {return_code();}
    ;

assignment:ID {push_lit(yylval);} T_assign {push_sign();} expression
          {
              codegen_assign();
              check_update(yylineno,name,value,type,scope);
          }

          ;


expression:lit 
          |lit bin_arop {push_sign();}expression {codegen();}
          |lit bin_boolop expression
          |lit un_arop {push_sign();codegen_un();}
          |un_arop expression
          |un_boolop expression
          ;

loops:FOR  cond_stmt_for { for1();} TO cond_stmt_for{for3();} DO loopbody{for4();}
     |FOR  cond_stmt_for { for1();} DOWN_TO cond_stmt_for{for3();} DO loopbody{for4();}

     | IF INS cond_stmt XTR THEN {if1();}  loopbody z{if3();}

     ;

z:ELSE_IF INS cond_stmt XTR {if2();} THEN loopbody x
 |empty
 ;

x:ELSE_IF INS cond_stmt XTR {if2();} THEN loopbody x
 |ELSE loopbody
 |empty
 ;

loopbody:OSCOPE c CSCOPE  T_semi
  	    |stmt T_semi
  	    ;



cond_stmt:stmt
         |cond
         ;

cond_stmt_for:stmt
             |cond
             |empty
             ;

cond:lit relop lit {codegen_assigna();}
    |lit relop lit bin_boolop lit relop lit
    |un_boolop'('lit relop lit')'
    |un_boolop lit relop lit
    |un_boolop'('lit')'
    ;

print:COUT INS COUTSTR XTR  T_semi
     ;

read_ip:CIN INS ID XTR  T_semi
       ;

lit:ID {push_lit(yylval);}
   |NUM {push_lit(value);}
   ;

TYPE:INT
    |CHAR
    |FLOAT
    |DOUBLE
    |BOOL
    ;

bin_arop:T_pl 
        |T_min 
        |T_mul
        |T_div
        ;

bin_boolop:T_and
          |T_or
          ;

un_arop:T_incr
       |T_decr
       ;

un_boolop:T_not
         ;

relop:T_lt {push_sign();}
     |T_gt {push_sign();}
     |T_lteq {push_sign();}
     |T_gteq {push_sign();}
     |T_neq {push_sign();}
     |T_eqeq {push_sign();}
     ;

%%
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
/*void return_code()//for the if clause
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
 quadlen++;

 temp_i++;
 label[++ltop]=lnum;
}*/

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
 printf("\tL%d: \n",y);
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
    printf("\tL%d: \n",y);
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
    printf("\tL%d: \n",lnum++);
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
    printf("\t%s = not %s\n",temp,st[top]);
    q[quadlen].op = (char*)malloc(sizeof(char)*4);
    q[quadlen].arg1 = (char*)malloc(sizeof(char)*strlen(st[top]));
    q[quadlen].arg2 = NULL;
    q[quadlen].res = (char*)malloc(sizeof(char)*strlen(temp));
    strcpy(q[quadlen].op,"not");
    strcpy(q[quadlen].arg1,st[top]);
    strcpy(q[quadlen].res,temp);
    quadlen++;
    //printf("\thi");
    printf("\tif %s goto L%d\n",temp,lnum);
    //printf("\thi");
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
    printf("\tgoto L%d\n",lnum);
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
    printf("\tL%d: \n",++lnum);
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
    printf("\tgoto L%d \n",l_for);

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

    printf("\tL%d: \n",x);

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
    printf("\tgoto L%d \n",lnum);

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

    printf("\tL%d: \n",x);

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
