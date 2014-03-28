%{
	#include <stdio.h>
	int vowel_count = 0;
%}

%%

[\t\n ]+	{}

[aeiouAEIOU]	{	vowel_count++;	}

.	{}

%%

int main()
{
	printf("Enter the string (press Ctrl+D to exit) : ");
	yylex();
	printf("Number of vowels are : %d.\n", vowel_count);
}