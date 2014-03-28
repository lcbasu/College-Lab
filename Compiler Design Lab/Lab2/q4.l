%{
	#include <stdio.h>
	#include <stdlib.h>
	
%}

%%

"DOUBLE" { 
	yytext = "FLOAT";
	fprintf(yyout, "%s", yytext);
	}

"double" { 
	yytext = "float";
	fprintf(yyout, "%s", yytext);
	}

"INT" { 
	yytext = "SHORT";
	fprintf(yyout, "%s", yytext);
	}

"int" { 
	yytext = "short";
	fprintf(yyout, "%s", yytext);
	}

. {
	fprintf(yyout, "%s", yytext);
	}

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