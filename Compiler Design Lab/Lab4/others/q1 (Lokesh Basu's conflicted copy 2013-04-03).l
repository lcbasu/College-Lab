%{
	#include "y.tab.h"
%}

%%

"while"	{	return WHL;	}
[-+_=><!0-9a-zA-Z]+	{	yylval.id = yytext;	return stmnt;	}
[-+_=><!;{}()]	{	return yytext[0];	}
.		{	ECHO;
			yyerror("unexpected character");	}

%%


int yywrap(void)
{
	return 1;
}