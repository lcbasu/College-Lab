%{
	#include <stdio.h>
	#include <stdlib.h>

	int c_line = 0;
	
%}

%%

"//"[a-zA-Z0-9' '\t]*	{

	c_line++;

}

"/*"[a-zA-Z0-9 \t\n]*"*""/"	{

	c_line++;

}

.	{

	fprintf(yyout, "%s", yytext);

}


%%

int main()
{
	char in_file_name[100];
	printf("Enter the input file name : ");
	scanf("%123s",in_file_name);

	char out_file_name[100];
	printf("Enter the output file name : ");
	scanf("%123s",out_file_name);

	extern FILE *yyin;
	extern FILE *yyout;

	yyin = fopen(in_file_name, "r");

	if(yyin == NULL)
		printf("\nError!!!\nCan't open the file.\n");

	yyout = fopen(out_file_name, "w");
	yylex();

	printf("\nTotal no of comment lines are : %d\n", c_line);

	fclose(yyin);
	fclose(yyout);

	return 0;
}