%{
#include <stdio.h>
%}

digit   [0-9]
letter  [a-zA-Z]
num     {digit}+
id      {letter}({letter}|{digit})*
aop     [+\-*/]
term    ({id}|{num})

%%
{id}={term}({aop}{term})*   { printf("valid\n"); }
\n                          ;
.                           { printf("invalid\n"); }
%%

int main() {
    yylex();
    return 0;
}
