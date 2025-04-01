%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(const char *s);
%}

%union {
    char *str;
    int num;
    float fnum;
    char cval;
}

%token <str> ID
%token <num> NUMBER
%token <fnum> FLOAT_NUMBER
%token <cval> CHAR_VALUE
%token INT FLOAT CHAR ASSIGN SEMICOLON COMMA

%%

program:
    statements
    ;

statements:
    statement
    | statements statement
    ;

statement:
    declaration SEMICOLON
    | assignment SEMICOLON
    | declaration_with_assignment SEMICOLON
    ;

declaration:
    INT ID { printf("Declared: int %s\n", $2); }
    | FLOAT ID { printf("Declared: float %s\n", $2); }
    | CHAR ID { printf("Declared: char %s\n", $2); }
    | INT ID COMMA ID { printf("Declared: int %s, %s\n", $2, $4); }
    | FLOAT ID COMMA ID { printf("Declared: float %s, %s\n", $2, $4); }
    | CHAR ID COMMA ID { printf("Declared: char %s, %s\n", $2, $4); }
    ;

assignment:
    ID ASSIGN NUMBER { printf("Assigned: %s = %d\n", $1, $3); }
    | ID ASSIGN FLOAT_NUMBER { printf("Assigned: %s = %.2f\n", $1, $3); }
    | ID ASSIGN CHAR_VALUE { printf("Assigned: %s = '%c'\n", $1, $3); }
    | ID ASSIGN NUMBER COMMA ID ASSIGN NUMBER { 
        printf("Assigned: %s = %d, %s = %d\n", $1, $3, $5, $7); 
    }
    ;

declaration_with_assignment:
    INT ID ASSIGN NUMBER { printf("Declared & Assigned: int %s = %d\n", $2, $4); }
    | FLOAT ID ASSIGN FLOAT_NUMBER { printf("Declared & Assigned: float %s = %.2f\n", $2, $4); }
    | CHAR ID ASSIGN CHAR_VALUE { printf("Declared & Assigned: char %s = '%c'\n", $2, $4); }
    ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    printf("Syntax error!\n");
}

