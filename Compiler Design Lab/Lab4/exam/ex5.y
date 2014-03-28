%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	void yyerror(char *s);
	int nWords = 0;
	extern FILE *yyin;
%}

%union	{char *wrd;}
%start	line
%token	<wrd>	WORD
%type	<num>	line exp term factor

%%

line	:	exp		{nWords++;}
		|	line exp	{nWords++;}
		;

exp	:	WORD		{$$ = $1;}
%%

int main()
{
	return yyparse();
}

void yyerror(char *s)
{
	printf("%s", s);
}
