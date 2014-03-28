%{
	void yyerror(char *s);
	#include <stdio.h>
	#include <stdlib.h>
	int totalIF = 0;
	int otherWords = 0;
%}

%start	line
%token	IF OTHER

%%

line	:	ifs	{	printf("\ncontains if statement\n");	}
		|	others	{	printf("\ncontains other statement\n");	}
		;

ifs	:	IF	{	totalIF++;	}
	;

others	:	OTHER	{	otherWords++;	}
		;


%%

int main()
{
	printf("\nEnter an expression\n");
	yyparse();		
	printf("\nNumber of IFs and OTHERS are : %d, %d\n", totalIF, otherWords);
	return 0;
}


void yyerror(char *s)
{
	printf("%s\n", s);
}