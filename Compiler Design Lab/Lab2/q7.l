%{

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	char in_str[100];
	int line_no = 1;
	void quicksort(char *arr, int p, int r);
	int partition(char *arr, int p, int r);


%}

%%

[\n]	{

	line_no++;

}

[a-zA-Z]+	{

	char yy_str[100];
	int k;
	for(k=0; k<yyleng; k++)
	{
		yy_str[k] = yytext[k];
	}
	yy_str[yyleng] = '\0';

	if(yyleng == strlen(in_str))
	{
		char *yytext_str = yytext;
		quicksort(yytext_str, 0, yyleng-1);

		int count=0;
		int i;		
		for(i=0; i<yyleng; i++)
		{
			if(yytext_str[i]==in_str[i])
			{
				count++;
			}
			else
				break;

		}
		if(count == yyleng)
			fprintf(yyout, "ANAGRAM [ %s ] present at line number : %d.\n",yy_str, line_no);
	}

}

.	{}

%%


void quicksort(char arr[], int p, int r)
{
	if(p<r)
	{
		int q = partition(arr, p, r);
		quicksort(arr, p, q-1);
		quicksort(arr, q+1, r);
	}
}

int partition(char arr[], int p, int r)
{
	int x = arr[r];
	int i = p-1;
	int j;
	for(j=p; j<r; j++)
	{
		if(arr[j]<=x)
		{
			i = i+1;
			char temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	char temp = arr[i+1];
	arr[i+1] = arr[r];
	arr[r] = temp;
	return i+1;
}



int main()
{
	char in_file_name[100];
	printf("Enter the input file name : ");
	scanf("%123s",in_file_name);

	printf("Enter the string : ");
	scanf("%s",in_str);
	quicksort(in_str, 0, strlen(in_str)-1);

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