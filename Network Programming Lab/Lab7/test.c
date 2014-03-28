#include <stdio.h>
#include "mcrypt.h"
#include <string.h>

int checkPalindrome(char *a)
{
	int length = strlen(a);

	int i;

	for(i = 0; i < length/2; i++)
	{
		if(a[i] != a[length-i-1])
		{
			return 0;	//not a palindrome
		}
	}
	return 1;	//is palindrome
}


int main()
{
	if(checkPalindrome("aaab"))
		printf("Yes\n");
	else
		printf("No\n");

	char stop[1999] = "stop";

	printf("%d\n", strcmp(stop, "stop"));
	return 0;
}