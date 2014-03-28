%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	int words = 0;
	char *wList[1000];
	int isUnique(char *w);
%}

%%

[^ \t\n]+	{if(isUnique(yytext)){strcpy(wList[words],yytext);words++;}}

%%

int isUnique(char *w)
{
	int result = 1;
	int i;
	for(i = 0; i < words; i++)
	{
		if(strcmp(wList[i], w) == 0)
		{
			result = 0;
			break;
		}
	}
	return result;
}

int main()
{
	yyin = fopen("in.cpp", "r");
	yylex();
	printf("%d\n", words);
	return 0;
}
