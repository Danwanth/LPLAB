%{
#include <stdio.h>

int vowels = 0, consonants = 0, digits = 0, special = 0;
%}

%%
[aeiouAEIOU] { vowels++; }
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ] { consonants++; }
[0-9] { digits++; }
[^a-zA-Z0-9 \n\t] { special++; }
[ \t\n] ;
%%

int main() {
    yylex();
    printf("Vowels      : %d\n", vowels);
    printf("Consonants  : %d\n", consonants);
    printf("Digits      : %d\n", digits);
    printf("Special Char: %d\n", special);
    return 0;
}

int yywrap() {
    return 1;
}

