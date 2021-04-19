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
int l_while=0;
int l_for=0;


typedef struct node   //symbol table 2D arr
{
	int line;
    int scope;
	char* name;
	char* value;
	char* type; 
} node;
typedef struct quadruples //2D arr
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

    void createNode(int line, char* name, char* value, char* type, int scope);
	void AddUpdateNode(int line,char* name,char* value,char* type, int scope);
    void update(int line,char* name,char* value,char* type, int scope);
	void printTable();
	void pushSignop();
	void pushVal(char* yy);
	void assignmentCodegen();
	void codegen();
	void assignmentCodegena();
	void unaryCodegen();
	void if1();
	void if2();
	void if3();
	void while1();
	void while2();
	void while3();
	
    void createNode(int line, char* name, char* value, char* type, int scope)
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
    void AddUpdateNode(int line,char* name,char* value,char* type, int scope)
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
			createNode(line,name,value,type,scope);
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
    void printTable()
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
    
     void temp_AddUpdateNode(char* name,char* value,char* type, int scope)
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
     void label_AddUpdateNode(char* name, char* value, char* type, int scope)
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
%token T_lt T_gt T_lteq T_gteq T_neq T_eqeq T_pl T_min T_mul T_div T_and T_or T_incr T_decr T_not T_eq T_assign T_comma T_semi T_dot T_END WHILE
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
              AddUpdateNode(yylineno,name,"",type,scope);
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
    |expression {$$=$1;}
    |print
    |read_ip
    ;

assignment:ID {pushVal(yylval);} T_assign {pushSignop();} expression
          {
              assignmentCodegen();
              check_update(yylineno,name,value,type,scope);
          }
          |
          error  {
           
            yyerrok;
            yyclearin;
            }

          ;


expression:lit {$$=$1;}
          |lit bin_arop {pushSignop();}expression {codegen();}
          |lit bin_boolop expression
          |lit un_arop {pushSignop();unaryCodegen();}
          |un_arop expression
          |un_boolop expression 
          ;

loops:WHILE {while1();} INS cond_stmt XTR {while2();} DO loopbody {while3();} 
     |IF INS cond_stmt XTR THEN {if1();}  loopbody z{if3();}
     | empty

     ;

z:ELSE_IF INS cond_stmt XTR {if2();} THEN loopbody x
 ;

x:ELSE_IF INS cond_stmt XTR {if2();} THEN loopbody x
 |ELSE loopbody
 ;

loopbody: OSCOPE c CSCOPE 
  	    |stmt T_semi
  	    ;



cond_stmt:stmt
         |cond
         ;

cond_stmt_for:stmt
             |cond
             |empty
             ;

cond:lit relop lit {assignmentCodegena();}
    |lit relop lit bin_boolop lit relop lit
    |un_boolop INS lit relop lit XTR
    |un_boolop lit relop lit
    |un_boolop INS lit XTR
    ;

print:COUT INS COUTSTR XTR  T_semi
     ;

read_ip:CIN INS ID XTR  T_semi
       ;

lit:ID {pushVal(yylval);}
   |NUM {pushVal(value);}
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

relop:T_lt {pushSignop();}
     |T_gt {pushSignop();}
     |T_lteq {pushSignop();}
     |T_gteq {pushSignop();}
     |T_neq {pushSignop();}
     |T_eqeq {pushSignop();}
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
		printTable();
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
void pushVal(char* yy)
{
	strcpy(st[++top],yy);
}

void pushSignop()
{
//printf("\t%s\n",yytext);
strcpy(st[++top],yytext);
}
void assignmentCodegen()   // for assignment operations
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
void unaryCodegen()  //unary and temps
{
    //printf("\thi");
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    //printf("\ttemporaries\n");
    temp_AddUpdateNode(temp, "-", "temp",scope);
     //void AddUpdateNode(int line,char* name,char* value,char* type, int scope)
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

}
void codegen()
{
    strcpy(temp,"T");
    sprintf(tmp_i, "%d", temp_i);
    strcat(temp,tmp_i);
    //printf("\ttemporaries\n");
    temp_AddUpdateNode(temp, "-", "temp",scope);
     //void AddUpdateNode(int line,char* name,char* value,char* type, int scope)
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
void while1() //Label first because while gets degenerated to if, and it needs to evaluate the label before the body  (multiplechecks)
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
    label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
    quadlen++;
}

void while2() // condition
{
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_AddUpdateNode(temp, "-", "temporary",scope);
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
     label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
    quadlen++;

 temp_i++;
 }

void while3() // inside the label
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
     label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
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
     label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
    quadlen++;
}


void if1()//for the if clause
{
	//printf("\there");
 lnum++;
 strcpy(temp,"T");
 sprintf(tmp_i, "%d", temp_i);
 strcat(temp,tmp_i);
 temp_AddUpdateNode(temp, "-", "temp",scope);
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
 label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
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
 temp_AddUpdateNode(temp, "-", "temp",scope);
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
 label_AddUpdateNode(q[quadlen].res, "-", "label",scope);
 quadlen++;
	
 temp_i++;
 label[++ltop]=lnum;
}

void assignmentCodegena()//for  conditions
{
	strcpy(temp,"T");
	sprintf(tmp_i, "%d", temp_i);
	strcat(temp,tmp_i);
	temp_AddUpdateNode(temp, "-", "temp",scope);
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
