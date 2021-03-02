
/* BLOCK A: Statements block*/
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>
#include "hashtbl.c" //include the hash table
HASHTBL *symbol; //Symbol Table declaration (global)
#define atoa(x) #x

//#define MAX_LINE_SIZE 256

char filename[64];
extern int line_no;

extern FILE *yyin;
int scope; //global variable for scope, initialized to 0
int datatype; 
error_no = 0; 
//global variable for error count initialized to 0

%}

%union {
  unsigned int integer;
  double real;
  char *string;
  char character;
  int boolean;
}


//keywords
%token <string> T_PROGRAM T_CONST T_TYPE T_ARRAY T_OF T_VAR T_FORWARD T_FUNCTION T_PROCEDURE T_INTEGER T_REAL T_BOOLEAN T_CHAR T_STRING T_BEGIN T_END T_IF T_THEN T_ELSE T_WHILE T_DO T_FOR T_DOWNTO T_TO T_READ T_WRITE T_LENGTH T_ID T_SCONST//T_OTHERWISE T_CASE T_EOF 

//integer consts
%token <integer> T_ICONST

//real consts
%token <real> T_RCONST

//logical
%token <boolean> T_BCONST

//chars
%token <character> T_CCONST

%type <string>	identifiers typename expression variable type_defs read_item assignment iter_space
%type <integer> constant  



//operators
%token <string> 
T_RELOP
T_ADDOP
T_OROP
T_MULDIVANDOP
T_NOTOP
T_LPAREN
T_RPAREN
T_SEMI
T_DOT
T_COMMA
T_COLON
T_LBRACK
T_RBRACK
T_ASSIGN
T_DOTDOT
T_EQU

//assoc and priority (operators)
%nonassoc T_COLON
%nonassoc T_LBRACK T_RBRACK
%left T_OROP
%nonassoc T_RELOP
%nonassoc T_NOTOP
%left T_ADDOP
%left T_MULDIVANDOP
%right T_EQU
%nonassoc T_LPAREN T_RPAREN

//solving dangling else
%nonassoc T_THEN
%nonassoc T_ELSE

//start symbol of the Grammar = program
//%start program;


%%
/*BLOCK B: Rules block*/

program: header declarations subprograms comp_statement T_DOT 
    ;

header: T_PROGRAM T_ID T_SEMI 
| error  {
           
            yyerrok;
            yyclearin;
            }
    ;

declarations: constdefs typedefs vardefs 
| error  {
            yyerrok;
            yyclearin;
            printf("Syntax error in Variable\n");    
            }
  

constdefs: T_CONST constant_defs T_SEMI 

    |/*empty*/
    ;
        
constant_defs: constant_defs T_SEMI T_ID T_EQU expression 
    | T_ID T_EQU expression  {hashtbl_insert(symbol,$1,$3,scope,"constant",line_no);}
    ;
            
expression: expression T_RELOP expression
    | expression T_EQU expression
    | expression T_OROP expression
    | expression T_ADDOP expression
    | expression T_MULDIVANDOP expression
    | T_ADDOP expression
    | T_NOTOP expression
    | variable {$$ = $1;}
    | T_ID T_LPAREN expressions T_RPAREN
    | T_LENGTH T_LPAREN expression T_RPAREN
    | constant { $$ =$1;} 
    | T_LPAREN expression T_RPAREN
   
    ;
            
variable: T_ID { $$ = $1;}
    | variable T_LBRACK expressions T_RBRACK 
     | error  {
            yyerrok;
            yyclearin;
                    
            }
    
    ;
         
expressions: expressions T_COMMA expression 
    | expression 
    
    ;
            
constant: T_ICONST {$$ =$1; datatype=0;}
    | T_RCONST {$$ =$1; datatype =1;}
    | T_BCONST {$$ =$1; datatype=2;}
    | T_CCONST {$$ =$1; datatype=3;}
    | T_SCONST {$$ =$1;datatype=4;}
    ;
        
typedefs: T_TYPE type_defs T_SEMI
    |/*empty*/
    ;
        
type_defs: type_defs T_SEMI T_ID T_EQU type_def 
    | T_ID T_EQU type_def 
    ;
        
type_def: T_ARRAY T_LBRACK dims  T_RBRACK T_OF typename
    | T_LPAREN identifiers T_RPAREN
    | limit T_DOTDOT limit
    ;
        
dims: dims T_COMMA limits
    | limits
    ;
    
limits: limit T_DOTDOT limit
    | T_ID 
    ;
    
limit: sign T_ICONST
    | T_CCONST
    | T_BCONST
    | T_ADDOP T_ID 
    | T_ID
    ;
    
sign: T_ADDOP
    |/*empty*/
    ;
    
typename: T_INTEGER { $$ = $1; datatype=0;}
    | T_REAL { $$ = $1;  datatype=1;}
    | T_BOOLEAN { $$ = $1;  datatype=2;}
    | T_CHAR { $$ = $1;  datatype=3;}
    | T_STRING { $$ = $1;  datatype=4;}
    | T_ID {$$ = $1;}
    ;
    
    
vardefs: T_VAR variable_defs T_SEMI 
    |/*empty*/
    ;
    
variable_defs: variable_defs T_SEMI identifiers T_COLON typename {hashtbl_insert(symbol,$3,$5,scope,"NULL",line_no);}
    | identifiers T_COLON typename {hashtbl_insert(symbol,$1,$3,scope,"NULL",line_no);}
    
    ;
    
identifiers: T_ID { $$ = $1; }
    | identifiers T_COMMA T_ID 
                            { 
                            
                            //$$=$1; 
                            char res[10];
                            if(datatype==0)
                            {
                                hashtbl_insert(symbol,$3,"integer",scope,"NULL",line_no);

                            }
                            else if(datatype==1)
                            {
                                hashtbl_insert(symbol,$3,"real",scope,"NULL",line_no);
                            }
                            else if(datatype==2)
                            {
                                hashtbl_insert(symbol,$3,"boolean",scope,"NULL",line_no);
                            }
                            else if(datatype==3)
                            {
                                hashtbl_insert(symbol,$3,"character",scope,"NULL",line_no);
                            }
                            else if(datatype==4)
                            {
                                hashtbl_insert(symbol,$3,"string",scope,"NULL",line_no);
                            }
                            }
    ;
    
subprograms: subprograms subprogram T_SEMI
    |/*empty*/
    ;
    
subprogram: sub_header T_SEMI T_FORWARD
    | sub_header T_SEMI declarations subprograms comp_statement
    
    ;
    
sub_header: T_FUNCTION T_ID formal_parameters T_COLON typename
    | T_PROCEDURE T_ID formal_parameters
    | T_FUNCTION 
    ;
    
formal_parameters: T_LPAREN parameter_list T_RPAREN
    |/*empty*/
    ;
    
parameter_list: parameter_list T_SEMI pass identifiers T_COLON typename
    | pass identifiers T_COLON typename;
    
pass: T_VAR
    |/*empty*/
    ;
    
comp_statement: T_BEGIN statements T_END 

    ; 

statements: statements T_SEMI statement
    | statement
       
    | error  {
           // printf("Error at IF\n");
       
            yyerrok;
            yyclearin;
            
            }
    ;
    
statement: assignment 
    | if_statement
    | while_statement
    | for_statement
    | subprogram_call
    | io_statement
    | comp_statement
    |//empty
 
    ;
    
assignment: variable T_ASSIGN expression {
                                            printf("New values : %s, %d\n", $1,$3); 
                                            char result[4]; 
                                            int num = $3;
                                           
                                            sprintf(result, "%d", num); 
                                            hashtbl_update(symbol,$1,result);}
          
    ;

//shift-reduce error on IF: 
// combine if_statement & if_tail as one rule
// define prec&priority as: 
// %nonassoc T_THEN
// %nonassoc T_ELSE see ORilley page 208

if_statement: T_IF expression T_THEN statement T_SEMI
    | T_IF expression T_THEN statement T_SEMI T_ELSE statement
      
    ;
    
while_statement: T_WHILE  expression {scope++;} T_DO statement T_SEMI {hashtbl_get(symbol,scope);scope--;} 
    ;

for_statement: T_FOR T_ID T_ASSIGN  iter_space {scope++;} T_DO statement  {hashtbl_insert(symbol,$2,"integer",scope,"NULL",line_no); 
                                                                                    //hashtbl_get(symbol,scope);
                                                                                    scope--; 
}  
    ;

iter_space: expression T_TO expression {printf("EXPRESSION : %s",$1);}
    |  expression T_DOWNTO expression 
    ;
    
subprogram_call: T_ID
    | T_ID T_LPAREN expression T_RPAREN
    ;
    

io_statement: T_READ T_LPAREN read_list T_RPAREN
    | T_WRITE T_LPAREN write_list T_RPAREN 
    ;
    
read_list: read_list T_COMMA read_item
    | read_item
    ;
    
    
read_item: variable 
    ;

write_list: write_list T_COMMA write_item
    |write_item
    | 
    ;
    
write_item: expression 
    ;

%%
/*BLOCK C: Functions*/
int  main(int argc,char ** argv){
    int out;
    
    //check if an input file is passed as an argument
	if(argc<2){
        printf("No input file!\n");
		exit(1);
    }
		
	yyin = fopen(argv[1],"r");
    strcpy(filename, argv[1]);

    if (yyin == NULL) {
        printf("File not found!\n");
        exit(1);
    }
    
    //input file ok!
    
    //symbol table initialize/create
    if(!(symbol=hashtbl_create(16, NULL))) {
    fprintf(stderr, "ERROR: hashtbl_create() failed\n");
    exit(EXIT_FAILURE);
    }

        
    out=yyparse();
    

    if(!out) {// yyparse == 0 - parsing completed
    printf("\n\nParsing completed.\n\n");
    
    print_table(symbol);

    if(error_no ==0)
    {
        printf("\n------> No syntax errors.\n\n");
    }
    else if(error_no>0)
    {
        printf("\n------> %d errors.\n\n",error_no);
    }
    fclose(yyin);
    return(0);
    }
 
    
    else { //yyparse()==1 - could not complete parsing
        printf("Syntax analyzer failed\n");
        hashtbl_destroy(symbol);
        fclose(yyin); // close input file
        return(1);
    }

	
	
}




void yyerror(char *s) {
    error_no++;
    
    fprintf(stderr, "line %d: %s\n", line_no, s);
}

//cemetary -- things that i'm not 100% sure that must be erased

/*
statement: notif_statement
    | if_statement
    ;

    
notif_statement: assignment
    | while_statement
    | for_statement
    | subprogram_call
    | io_statement
    | comp_statement
    |//empty
    ;
    
if_statement: matched
    | unmatched
    ;
    
matched: T_IF expression T_THEN matched T_ELSE matched
    | notif_statement
    ;
    
unmatched: T_IF expression T_THEN if_statement
    | T_IF expression T_THEN matched T_ELSE unmatched
    ;

{Dp}({D})*[Ee][+-]?(({D})*{Dp}) {doubletoint = atof(yytext);yylval.integer = doubletoint;return(T_ICONST);}

(_)?{L}({L}|{D}|_)*({L}|{D})|{L}* {yylval.string = strdup(yytext); return(T_ID);} 
*/


