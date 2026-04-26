%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%token ACHAR

%%

S : S A
  | A
  ;

A : ACHAR ACHAR ACHAR ACHAR
  ;

%%

void yyerror(const char *s){
    printf("Invalid string\n");
    exit(1);
}

int main(){
    printf("Enter string of a's:\n");
    yyparse();
    printf("Valid string (multiple of 4 a's)\n");
    return 0;
}