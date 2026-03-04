%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'

%%
exp:
      exp '+' exp
    | exp '-' exp
    | exp '*' exp
    | exp '/' exp
    | NUMBER
    ;
%%

void yyerror(const char *s){
    printf("invalid exp\n");
    exit(1);
}

int main(){
    printf("enter arithmetic exp:\n");
    yyparse();
    printf("valid exp\n");
    return 0;
}

