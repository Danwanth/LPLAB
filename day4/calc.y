%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
int result;
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
input : expr        { result = $1; }
      ;

expr  : expr '+' expr   { $$ = $1 + $3; }
      | expr '-' expr   { $$ = $1 - $3; }
      | expr '*' expr   { $$ = $1 * $3; }
      | expr '/' expr   {
                            if ($3 == 0) {
                                printf("Division by zero error\n");
                                exit(0);
                            }
                            $$ = $1 / $3;
                        }
      | '(' expr ')'    { $$ = $2; }
      | NUMBER          { $$ = $1; }
      ;
%%

int yyerror(const char *s)
{
    printf("Invalid Expression\n");
    return 0;
}

int main()
{
    printf("Enter expression: ");
    yyparse();
    printf("Result = %d\n", result);
    return 0;
}

