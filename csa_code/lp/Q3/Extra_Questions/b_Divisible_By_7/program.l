%{
#include <stdio.h>
int n;
%}
digit [0-9]
%%
{digit}+ {
    n = atoi(yytext);
    if (n % 7 == 0)
        printf("%d is Divisible by 7\n", n);
    else
        printf("%d is Not Divisible by 7\n", n);
}
. ;
%%
int main() {
    yyin = stdin;
    yylex();
    return 0;
}
