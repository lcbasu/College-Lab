#include <stdio.h>

char sum[4];

void findSum(char ipheader[10][4] , int *carryPtr)
{
	int i,j;
	int sumPtr = 3;
	for(i = 3; i >=0; i--)//column
	{
		int d;
		int colSum = 0;
		for(j = 0; j < 10; j++)//row
		{
			d = ipheader[j][i];
			if(d >= 65 && d <= 70)
				d = d - 55;
			else
				d = d - 48;
			colSum = colSum + d;
		}
		colSum = colSum + *carryPtr;
		int placeDigit = colSum % 16;
		if(placeDigit > 9)
		{
			char c = 'A';
			placeDigit = placeDigit - 10;	//13-10 = 3 --> 'A'+3 = D
			char finalChar = c + placeDigit;
			sum[sumPtr] = finalChar;
			sumPtr--;
		}
		else
		{
			char finalChar = (((int)'0')+placeDigit);//4 = 48+4 in char so to keep 4 = '4' we do this conversion
			sum[sumPtr] = finalChar;
			sumPtr--;
		}
		*carryPtr = colSum/16;
	}
}

int veifyChecksum(char ipheader[10][4], int *carryPtr)
{
	findSum(ipheader, carryPtr);

	int carry = *carryPtr;

	int i,j;
	if(carry>0)
	{
		for(j = 3; j >= 0; j--)//row
		{
			int tempSum = 0;
			int d = sum[j];
			if(d >= 65 && d <= 70)
				d = d - 55;
			else
				d = d - 48;

			tempSum = tempSum + d + carry;

			int placeDigit = tempSum % 16;

			if(placeDigit > 9)
			{
				char c = 'A';
				placeDigit = placeDigit - 10;	//13-10 = 3 --> 'A'+3 = D
				char finalChar = c + placeDigit;
				sum[j] = finalChar;
			}
			else
			{
				char finalChar = (((int)'0')+placeDigit);//4 = 48+4 in char so to keep 4 = '4' we do this conversion
				sum[j] = finalChar;
			}
			carry = tempSum/16;
		}
		printf("Sum :\t");
		for(i = 0; i < 4; i++)
		{
			printf("%c ", sum[i]);
		}
		printf("\n");		
		}
	else
	{
		printf("Sum after :\t");
		for(i = 0; i < 4; i++)
		{
			printf("%c ", sum[i]);
		}
		printf("\n");		
	}

	for (i = 0; i < 4; i++)
	{
		if(sum[i] != 'F')
			return 0;	//1-> true 0->false
	}
	return 1;
}


int main()
{
	char ipheader[10][4];
	printf("Enter the IP Header :\t");
	int i,j;
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 4; j++)
		{
			scanf("%c", &ipheader[i][j]);
		}
	}
	printf("IP Header\n");
	printf("---------\n");
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 4; j++)
		{
			printf("%c", ipheader[i][j]);
		}
		printf("\n");
	}	
	int carry = 0;



	int result = veifyChecksum(ipheader, &carry);

	if(result == 1)
		printf("Verified\n");
	else
		printf("Not Verified\n");

	return 0;
}