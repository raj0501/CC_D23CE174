
%{
#include <stdio.h>
#include <stdbool.h>

int length = 0;
bool has_lower = false;
bool has_upper = false;
bool has_digit = false;
bool has_symbol = false;
%}

%%

[a-z]          { has_lower = true; length++; } 
[A-Z]          { has_upper = true; length++; }  
[0-9]          { has_digit = true; length++; }  
[*;#$@]        { has_symbol = true; length++; } 
.              { length++; }                    
\n             { /* End of input */ }

%%

int main() {
    yylex();  /* Invoke the lexical analyzer */

    if (length >= 9 && length <= 15 && has_lower && has_upper && has_digit && has_symbol) {
        printf("Valid password\n");
    } else {
        printf("Invalid password\n");
    }

    return 0;
}
int yywrap() 
{
    return 1;
}