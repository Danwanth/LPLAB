%{
#include <stdio.h>
%}

digit [0-2]

%%
{digit}[0][0]   { printf("Valid\n"); }
{digit}[1][1]   { printf("Valid\n"); }
{digit}[2][2]   { printf("Valid\n"); }
[^\n]+          { printf("Invalid\n"); }
\n              ;
%%

int main() {
    yylex();
    return 0;
}
