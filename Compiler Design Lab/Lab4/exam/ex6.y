%{

	#include <stdlib.h>
	#include <stdio.h>
	void yyerror(char *s);

%}

%union	{int num;}
%start	line
%token	<num>	NUMBER
%type	<num>	line exp term factor

%%

line	:	exp ';'	{printf("%d\n", $1);}
	|	line exp ';'	{printf("%d\n", $2);}
	;
exp	:	term	{$$ = $1;}
	|	exp '+'	term {$$ = $1 + $3;}
	;

term	:	factor	{$$ = $1;}
	|	term '*' factor	{$$ = $1 * $3;}
	;

factor	:	NUMBER	{$$ = $1;}

%%

void yyerror(char *s)
{
	printf("%s", s);
}

int main()
{
	return yyparse();
}
