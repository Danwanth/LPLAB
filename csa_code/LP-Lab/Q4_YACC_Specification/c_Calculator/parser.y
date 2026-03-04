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
    input line
    |
    ;
line:
    expr '\n'   { printf("Result = %d\n", $1); }
    ;
expr:
    expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { $$ = $1 / $3; }
    | '(' expr ')'  { $$ = $2; }
    | NUM            { $$ = $1; }
    ;
%%
void yyerror(const char *s)
{
    printf("Error\n");
}
int main()
{
    printf("Arithmetic Calculator:\n");
    yyparse();
    return 0;
}
