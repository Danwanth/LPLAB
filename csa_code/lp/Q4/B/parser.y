%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}
%token IF ELSE ID NUM
%nonassoc IFX
%nonassoc ELSE
%%
stmt:
    IF '(' cond ')' stmt %prec IFX
    | IF '(' cond ')' stmt ELSE stmt
    | ID ';'
    ;
cond:
    ID
    | NUM
    ;
%%
void yyerror(const char *s)
{
    printf("Invalid if-else statement\n");
}
int main()
{
    printf("Enter an if-else statement:\n");
    if (yyparse() == 0)
        printf("Valid if-else statement\n");
    return 0;
}
