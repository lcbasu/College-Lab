%{
	#include <stdio.h>
	int vowel_count = 0;
	int ws_count = 0;
%}

%%

[\t\n ]+	{
	printf("%c", yytext[0]);
	}

":" { 
	yytext = ",";
	printf("%s", yytext);
	}

"," { 
	yytext = "@";
	printf("%s", yytext);
	}

";" { 
	yytext = ":";
	printf("%s", yytext);
	}

. {
	printf("%s", yytext);
	}

%%

int main()
{
	printf("Enter the string (press Ctrl+D to exit) : \n");
	yylex();
}