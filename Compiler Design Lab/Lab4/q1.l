%{
	#include "y.tab.h"
%}

%%

"while"	{	return WHL;	}

[^ \t\n]	{	yylval.id = yytext;	return stmnt;	}


%%


int yywrap(void)
{
	return 1;
}