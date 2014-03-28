%{
	void yyerror(char *s);
	#include <stdio.h>
	#include <stdlib.h>

	int symbols[52];
	int symbolVal(char symbol);
	void updateSymbolVal(char symbol, int val);
	void message(int a, char sym, int b);
	
%}

%union	{	int num; char id;	}
%start	line
%token	print
%token	exit_command
%token	<num>	number
%token	<id>	identifier
%type	<num>	line exp term factor
%type	<id>	assignment

%%

line	:	assignment ';'	{	;	}
		|	comparision ';'	{	;	}
		|	exit_command ';'	{	exit(EXIT_SUCCESS);	}
		|	print exp ';'	{	printf("Result : %d\n", $2);	}
		|	line assignment ';'	{	;	}
		|	line comparision ';'	{	;	}
		|	line exit_command ';'	{	exit(EXIT_SUCCESS);	}
		|	line print exp ';'	{	printf("Result : %d\n", $3);	}		
		;

assignment	:	identifier '=' exp	{	updateSymbolVal($1, $3);	}
			;

comparision	:	term '<' term	{	message($1, '<', $3);		}
			|	term '>' term	{	message($1, '>', $3);		}
			|	term '#' term	{	message($1, '#', $3);		}
			|	term '!' term	{	message($1, '!', $3);		}
			|	term '%' term	{	message($1, '%', $3);		}
			|	term '@' term	{	message($1, '@', $3);		}
			;			

exp	:	term	{	$$ = $1;	}			
	;
term   : factor                         {$$ = $1;}
       ;

factor :	number                         {$$ = $1;}
       |    identifier	{	$$ = symbolVal($1);	}   
       ;

%%

int computeSymbolIndex(char token)		
{
	int indx = -1;
	if(islower(token))
		indx = token - 'a' + 26;
	else if(isupper(token))		
		indx = token - 'A';
	
	return indx;		
}

int symbolVal(char symbol)
{
	return symbols[computeSymbolIndex(symbol)];
}

void updateSymbolVal(char symbol, int val)
{
	symbols[computeSymbolIndex(symbol)] = val;
}

void message(int a, char sym, int b)
{
	if(sym == '<')
	{
		if(a < b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	if(sym == '>')
	{
		if(a > b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	if(sym == '#')
	{
		if(a == b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	if(sym == '!')
	{
		if(a != b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	if(sym == '%')
	{
		if(a >= b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
	if(sym == '@')
	{
		if(a <= b)
			printf("TRUE\n");
		else
			printf("FALSE\n");
	}
}

int main(void)
{
	int i;
	for(i = 0; i < 52; i++)
		symbols[i] = 0;
	return yyparse();		
}

void yyerror(char *s)
{
	printf("%s\n", s);
}