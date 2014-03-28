%{
	#include "y.tab.h"
%}

%%

[0-9]+	{	yylval.a_number = atoi(yytext); return number;	}
[a-zA-Z][0-9a-zA-Z]	{	yylval.a_variable = yytext[0]; return variable;	}
[ \t\n]	;
[-+/*=><!;{}()]	{	return yytext[0];	}
.		{	ECHO;
			yyerror("unexpected character");	}

%%


int yywrap(void)
{
	return 1;
}