%{
	#include "y.tab.h"
%}
WS	[ \t\n]
%%

{WS}+"if"{WS}*"("	{	return IF;	}
.		{	return OTHER;	}

%%

int yywrap(void)
{
	return 1;
}