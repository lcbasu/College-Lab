%{
	#include <stdio.h>
	#include <stdlib.h>
%}

%%

[\t\n ]+	{}

if 		|
double	|
int		|
do		|
cout 	|
return	|
case	|
switch	|
then	|
include	{ 
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
	char in_file_name[100];
	printf("Enter the input file name : ");
	scanf("%123s",in_file_name);

	extern FILE *yyin;
	extern FILE *yyout;

	yyin = fopen(in_file_name, "r");

	if(yyin == NULL)
		printf("\nError!!!\nCan't open the file.\n");

	yyout = fopen("output_file.cpp", "w");

	yylex();

	fclose(yyin);
	fclose(yyout);

	return 0;
}