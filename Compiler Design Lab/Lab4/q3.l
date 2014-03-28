%{
#define YY_DECL extern int yylex()

#include "y.tab.h"

%}

%%
[ \t\n]  ;
[a-zA-Z0-9]+      {
	return STRING;
}
.     ;
%%

int yywrap(void)
{
	return 1;
}