%{
    #include "parser.tab.h"
    #include <stdlib.h>
%}
%%
[0-9]+          { yylval = atoi(yytext); return NUM; }
"/"             { return '/'; }
[ \t\n]         ;
.               ;
%%
int yywrap() { return 1; }
