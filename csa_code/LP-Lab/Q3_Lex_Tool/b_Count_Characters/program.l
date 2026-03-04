%{
#include <stdio.h>
int v=0,c=0,d=0,s=0;
%}
%%
[aeiouAEIOU]            { v++; }
[a-zA-Z]                { c++; }
[0-9]                   { d++; }
[ \t\n]                 ;
.      { s++; }
%%
int main()
{
    printf("Enter input: \n");
    yylex();
    printf("Vowels = %d\n",v);
    printf("Consonants = %d\n",c);
    printf("Digits = %d\n",d);
    printf("Special Characters = %d\n",s);
    return 0;
}
