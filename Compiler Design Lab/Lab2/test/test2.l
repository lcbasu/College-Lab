%{
	#include <stdio.h>
%}

%%

[0-9]+	{	printf("Integer found : %s.\n", yytext);	}

.	{}

%%

int main()
{
	printf("Enter any string (press Ctrl+D to exit : )");
	yylex();
	return 0;
}