%{
	void yyerror(char *s);
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
%}

%union	{	char *id;	}
%start	line
%token	hfdfWHL
%token	stmnt
%token	exit_command
%type	<id>	expression

%%


line	:	expression ';'	{	;	}
		|	exit_command ';'	{	exit(EXIT_SUCCESS);	}
		|	line expression ';'	{	;	}
		|	line exit_command ';'	{	exit(EXIT_SUCCESS);	}		
		;

expression	:	WHL condtn st	{	printf("\nValid\n");	}
			;

condtn		:	'('	stmnt')'
			;

st 			:	simple
			|	'{' complex '}'
			|	expression
			;

simple		:	stmnt ';'
			|	';'
			;

complex		:	simple complex
			|	expression	complex
			|	simple
			|	expression
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