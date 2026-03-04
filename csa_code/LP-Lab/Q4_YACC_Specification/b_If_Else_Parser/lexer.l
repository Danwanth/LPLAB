%{
#include "y.tab.h"
%}
%%
"if"            { return IF; }
"else"          { return ELSE; }
[a-zA-Z]+       { return ID; }
[0-9]+          { return NUM; }
[();]           { return yytext[0]; }
[ \t\n]         ;
.               ;
%%
int yywrap()
{
    return 1;
}
