%{
#include <stdio.h>
FILE *yyin;
%}
%%
[a-zA-Z0-9._]+@[a-zA-Z0-9.]+\.[a-zA-Z]{2,}    { printf("%s\n",yytext); }
.|\n                                                 ;
%%
int main()
{
    yyin = fopen("example.txt", "r");
    if (!yyin) {
        perror("example.txt");
        return 1;
    }
    yylex();
    fclose(yyin);
    return 0;
}