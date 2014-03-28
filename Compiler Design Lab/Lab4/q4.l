%{

	#include"y.tab.h"

%}

%%

[0-9]+  {yylval=atoi(yytext); return NUM;}

\n      return 0;

.       return *yytext;

%%

int yywrap()
{
    return 1;
}