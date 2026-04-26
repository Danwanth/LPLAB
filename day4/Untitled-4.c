%{
#include "y.tab.h"
%}

%%
a   { return ACHAR; }
\n  { return 0; }
.   { return yytext[0]; }
%%