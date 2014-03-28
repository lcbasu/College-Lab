%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%%

[\t\n ]+	{}

if 		|
class	|
div		|
do		|
file 	|
begin	|
write	|
program	|
end		|
writeln	{ 
	fprintf(yyout, "%s --> KEYWORD\n", yytext);
	}


[0-9]+ {
	fprintf(yyout, "%s --> INTEGER\n", yytext);
	}

[0-9]+"."[0-9]* { 
	fprintf(yyout, "%s --> FLOATING POINT\n", yytext);
	}
[a-zA-Z][a-zA-Z0-9]*	{

	fprintf(yyout, "%s --> IDENTIFIER\n", yytext);

}

"+"		|
"-"		|
"*" 	|
"/" 	{

	fprintf(yyout, "%s --> OPERATOR\n", yytext);

}

"{"[a-zA-Z0-9\n  \t]*"}"	{

	fprintf(yyout, "%s --> COMMENT\n", yytext);

}

"("[a-zA-Z0-9 \t]");"	{}

. {}

%%

int main()
{

	extern FILE *yyin;
	extern FILE *yyout;

	yyin = fopen("in.pascal", "r");

	if(yyin == NULL)
		printf("\nError!!!\nCan't open the file.\n");

	yyout = fopen("output_file.pascal", "w");

	yylex();

	fclose(yyin);
	fclose(yyout);

	return 0;
}