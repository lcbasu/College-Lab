%{
	
	#include <stdio.h>	
	#include <stdlib.h>
	#include <string.h>

	void yyerror(char *s);

%}

%start	line
%token	FN
%token	FA1
%token	FA2

%%

line	:	exp	';'		{	;	}
		;

exp		:	FN FA1 FA2	{	printf("\nAccepted\n");	}
		;

%%

int main(void)		
{
	return yyparse();
}

void yyerror(char *s)
{
	printf("%s\n", s);
}