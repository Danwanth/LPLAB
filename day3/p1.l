%{
#include <stdio.h>
%}

%%

[0-9]+      { printf("Integer: %s\n", yytext); }
[0-9]+\.[0-9]+  { printf("Floating Point Number: %s\n", yytext); }
[\+\-\*/]   { printf("Arithmetic Operator: %s\n", yytext); }

.|\n        { /* Ignore other characters */ }

%%

int main() {
    yylex();
    return 0;
}

