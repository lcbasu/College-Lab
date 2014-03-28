#include <stdio.h>
#include <string.h>

char *ID_TABLE[100];

int main()
{
	ID_TABLE[0] = "Hello";
	char c[] = "Hell";
	if(strcmp(c, ID_TABLE[0]) == 0)
		printf("TRUE\n");
	else
		printf("FALSE\n");	
	return 0;
}