%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(const char *s);   
%}
%token FOR NUM ID
%%
stmt:
    FOR '(' ID '=' cond ';' ID aop cond ';' ID ep ')' '{' ID '=' NUM ';' '}'
    ;
cond:
    ID
    | NUM
    ;
ep:
    '+' '+'
    | '-' '-'
    ;
aop:
    '>'
    | '<'
    ;
%%
void yyerror(const char *s) {
    printf("Invalid for loop\n");
}

int main() {
    if (yyparse() == 0)
        printf("Valid for loop\n");
    return 0;
}
