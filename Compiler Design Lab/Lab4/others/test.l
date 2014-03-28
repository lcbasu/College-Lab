%{
#define YY_DECL extern int yylex()

#include "y.tab.h"  // to get the token types that we return

%}

%%
[ \t\n]  ;
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return FLOAT; }
[0-9]+            { yylval.ival = atoi(yytext); return INT; }
.     ;
%%

int yywrap(void)
{
	return 1;
}