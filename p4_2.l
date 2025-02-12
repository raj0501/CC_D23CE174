%{
#include <stdio.h>
#include <string.h>
%}

%%
[Cc][Hh][Aa][Rr][Uu][Ss][Aa][Tt]   { printf("university"); }  
.|\n                               { putchar(yytext[0]); }   
%%
int main() {
    yylex(); 
    return 0;
}
int yywrap() 
{
    return 1;
}