
%{
	#include "y.tab.h"
%}

%%

while				return WHILE;
[A-Za-z]([A-Za-z]|[0-9])*	return ID;
[0-9]+				return NUM;
[ \t]				;
\n				yyterminate();
.				return yytext[0];

%%
