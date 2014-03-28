%{
	#include "y.tab.h"
%}

%%


"a"	{	return A;	}
"b"	{	return B;	}
[ \t\n]	;
[+*=;()]	{	return yytext[0];	}
.		{	ECHO;
			yyerror("unexpected character");	}

%%

int yywrap(void)
{
	return 1;
}