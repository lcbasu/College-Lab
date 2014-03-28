%{
	#include "y.tab.h"
%}

%%

[0-9]+	{yylval.num = atoi(yytext);return NUMBER;}
[*+-;]	{return yytext[0];}
[ \n\t]	{;}
.	{ECHO;printf("unexpected character");}

%%

int yywrap()
{
	return 1;
}
