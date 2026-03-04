%{
#include <stdio.h>
%}
digit [0-9]
aop [+|\-|*|/|%]
%%
{digit}+                {printf("%s is an Integer\n",yytext);}
{digit}*"."{digit}+     {printf("%s is a floating point\n",yytext);}
{aop}                   {printf("%s is an Arithmetic Operator\n",yytext);}
[\t\n]+                 ;
.                       ;
%%
int main()
{
    printf("Enter Input: \n");
    yylex();
    return 0;
}