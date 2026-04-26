%{
#include "y.tab.h"
#include <stdlib.h>
%}
%%
[0-9]+          { yylval = atoi(yytext); return NUM; }
[()+\-*/]       { return yytext[0]; }
\n              { return '\n'; }
[ \t]           ;
.               ;
%%
int yywrap()
{
    return 1;
}
