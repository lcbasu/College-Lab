%{
	void yyerror(char *s);
	#include <stdio.h>
	#include <stdlib.h>
%}

%start line
%token A 
%token B

%%


line	:	expression ';'	{	;	}
		|	line expression ';'	{	;	}		
		;

expression	:	sa sb	{	printf("\nValid\n");	}
			|	sa 		{	printf("\nValid\n");	}
			|	sb 		{	printf("\nValid\n");	}
			;

sa 		: 	A
		|	A sa
		;
sb 		:	B
		|	B sb
		;

%%

int main(void)
{
	printf("Enter the string to be checked : ");
	yyparse();
	return 0;
}

void yyerror(char *s)
{
	printf("%s\n", s);
}