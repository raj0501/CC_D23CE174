%{
#include <stdio.h>
%}
%%
"int"|"char"|"float"|"return"  { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*         { printf("Identifier: %s\n", yytext); }
[0-9]+                         { printf("Constant: %s\n", yytext); }
\'[^\']\'                      { printf("String: %s\n", yytext); }
"//".*                         { printf("Comment: %s\n", yytext); }
"/*"([^\*]|(\*+([^\*/])))*"\*/" { printf("Comment: Block comment\n"); }
[{}();,]                       { printf("Punctuation: %s\n", yytext); }
[=+*/-]                        { printf("Operator: %s\n", yytext); }
[ \t\n]                        { /* Ignore whitespaces */ }
.                              { printf("Lexical Error: %s\n", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
