%{
    #include "parser.tab.h"
%}
%%
"for"           { return FOR; }
[0-9]+          { return NUM; }
[a-zA-Z]+       { return ID; }
[();<>=+\-{}]   { return yytext[0]; }
[ \t\n]         ;
.               ;
%%
int yywrap() { return 1; }
