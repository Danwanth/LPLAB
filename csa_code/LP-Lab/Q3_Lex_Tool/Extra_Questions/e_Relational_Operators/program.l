%{
#include <stdio.h>
%}

rop (<|>|<=|>=|!=|==)

%%
{rop}       { printf("Valid\n"); }
[^\n]+      { printf("Invalid\n"); }
\n          ;
%%

int main() {
    yylex();
    return 0;
}
