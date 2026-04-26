%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token NUM
%left '+' '-'
%left '*' '/'
%%
input:
    expr        { printf("Valid Expression\n"); }
    ;
expr:
    expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '(' expr ')'
    | NUM
    ;
%%
void yyerror(const char *s)
{
    printf("Invalid Expression\n");
}
int main()
{
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}
