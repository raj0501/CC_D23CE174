%{
#include "y.tab.h"
#include <stdlib.h>
%}

DIGIT     [0-9]+
FLOAT_NUM [0-9]+(\.[0-9]+)?
CHAR_VAL  \'[a-zA-Z]\'
ID        [a-zA-Z_][a-zA-Z0-9_]*
WS        [ \t\r\n]+

%%

"int"    { return INT; }
"float"  { return FLOAT; }
"char"   { return CHAR; }
{ID}     { yylval.str = strdup(yytext); return ID; }
{DIGIT}  { yylval.num = atoi(yytext); return NUMBER; }
{FLOAT_NUM} { yylval.fnum = atof(yytext); return FLOAT_NUMBER; }
{CHAR_VAL}  { yylval.cval = yytext[1]; return CHAR_VALUE; }
"="      { return ASSIGN; }
";"      { return SEMICOLON; }
","      { return COMMA; }
{WS}     { /* Ignore whitespace */ }

.        { return yytext[0]; } /* Catch-all for unknown characters */

%%

int yywrap() { return 1; }

