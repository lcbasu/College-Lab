%{

	#include "y.tab.h"
%}

%%

[^ \t\n]	{ yylval.wrd = yytext; return WORD;}

.|\n	{;}

%%

int yywrap(void)
{
	return 1;
}
