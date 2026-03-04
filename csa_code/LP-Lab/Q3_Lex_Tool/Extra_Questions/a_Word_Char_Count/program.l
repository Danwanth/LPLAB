%{
    #include <stdio.h>    
    int w = 1, c = 0;
%}
sp [" "]
%%
{sp} {w++;}
. {c++;}
%%
int main(){
    yyin = stdin;
    yylex();
    printf("%d %d", w, c);
    return 0;
}