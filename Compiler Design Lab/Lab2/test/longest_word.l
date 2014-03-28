%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	char temp_str[100];
	int longest = 0;
%}

%%

[a-zA-Z]+	{
	if(yyleng>longest)
	{
		longest = yyleng;
		strcpy(temp_str,yytext);
	}
	fprintf(yyout,"%s", "KEY-OR-ID");
}

. {
	fprintf(yyout,"%s", yytext);
	}

%%

int main()
{
	extern FILE *yyin;
	extern FILE *yyout;
	yyin  = fopen("test_file.cpp", "r");
	if(yyin == NULL)
	{
		printf("Cant't open the file!!!");
		return -1;
	}

	yyout = fopen("output_file.cpp","w");

	yylex();

	printf("\n\nLonget word is : %s with length of %d.\n",temp_str, longest);

	fclose(yyin);
	fclose(yyout);

	return 0;	
}