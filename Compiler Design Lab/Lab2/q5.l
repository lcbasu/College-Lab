%{
	#include <stdio.h>
	#include <stdlib.h>
	
	char regular_expression[100];

%}

%%

regular_expression { 
	yytext = "XXXX";
	fprintf(yyout,"%s", yytext);
	}


. {
	fprintf(yyout, "%s", yytext);
	}

%%

int main(arg)
{
	
	printf("Enter the string : ");
	scanf("%123s",regular_expression);

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