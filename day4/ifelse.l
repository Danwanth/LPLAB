%{
#include "y.tab.h"
#include <string.h>
%}

%%
"if"        return IF;
"else"      return ELSE;

[a-zA-Z_][a-zA-Z0-9_]*   return ID;
[0-9]+      return NUMBER;

"=="|"<="|">="|"<"|">"  return RELOP;

";"         return ';';
"("         return '(';
")"         return ')';

[ \t\n]+    ;   /* ignore whitespace */

.           { printf("Invalid character: %s\n", yytext); }
%%

int yywrap() {
    return 1;
}

