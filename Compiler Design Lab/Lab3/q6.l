%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%%

[\t\n ]+	{}

if 	|
else	|
class	|
struct	|
int	|
cout 	|
return	|
case	|
switch	|
then	|
include	{ 
	fprintf(yyout, "%s --> INVALID IDENTIFIER [RESERVED KEYWORDS]\n", yytext);
	}


[0-9]+ {
	fprintf(yyout, "%s --> INTEGER\n", yytext);
	}

[0-9]+"."[0-9]* { 
	fprintf(yyout, "%s --> FLOATING POINT\n", yytext);
	}
[0-9]+"."[0-9]+"e"[+-]?[0-9]+ { 
	fprintf(yyout, "%s --> REAL NUMBER\n", yytext);
	}		
[_a-zA-Z][a-zA-Z0-9]*	{

	fprintf(yyout, "%s --> IDENTIFIER\n", yytext);

}

"+"		|
"-"		|
"*" 	|
"/" 	{

	fprintf(yyout, "%s --> OPERATOR\n", yytext);

}

"//"[a-zA-Z0-9' '\t]*	{

	fprintf(yyout, "%s --> COMMENT\n", yytext);

}

"/*"[a-zA-Z0-9' '\t\n]*"*""/" {

	fprintf(yyout, "%s --> COMMENT\n", yytext);

}

. {}

%%

int main()
{
	extern FILE *yyin;
	extern FILE *yyout;

	yyin = fopen("in.cpp", "r");

	if(yyin == NULL)
		printf("\nError!!!\nCan't open the file.\n");

	yyout = fopen("out.cpp", "w");

	yylex();

	fclose(yyin);
	fclose(yyout);

	return 0;
}
