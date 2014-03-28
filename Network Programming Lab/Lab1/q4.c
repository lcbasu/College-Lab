#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void crc(int *dividend, int *tmpDividend, int *generator, int genLen, int newSize);
int getStartIndex(int *tmpDividend, int newSize);


int main()
{
	char in[1000];
	printf("Enter The Frame :\t");
	scanf("%s",in);

	int frameLen = strlen(in);

	int degree;
	printf("Enter The Degree :\t");
	scanf("%d",&degree);

	int newSize = frameLen+degree;
	int *dividend = (int *)malloc(newSize*sizeof(int));

	int i;
	for (i = 0; i < frameLen; ++i)
	{
		int tmp = in[i]-'0';
		dividend[i] = tmp;
	}

	//appending a total of 'degree' zeros to the end
	for (i; i < newSize; ++i)
	{
		dividend[i] = 0;
	}

	int *tmpDividend = (int *)malloc(newSize*sizeof(int));

	for (i = 0; i < newSize; ++i)
	{
		tmpDividend[i] = dividend[i];
	}


	printf("Enter The Generator :\t");
	scanf("%s",in);	

	int genLen = strlen(in);

	int *generator = (int *)malloc(genLen*sizeof(int));
	for (i = 0; i < genLen; ++i)
	{
		int tmp = in[i]-'0';
		generator[i] = tmp;
	}	


	printf("Dividend :\t");
	for (i = 0; i < 15; ++i)
	{
		printf("%d ",tmpDividend[i]);
	}
	printf("\n");


	crc(dividend, tmpDividend, generator, genLen, newSize);


	return 0;
}

void crc(int *dividend, int *tmpDividend, int *generator, int genLen, int newSize)
{
	while((getStartIndex(tmpDividend, newSize) <= (newSize - genLen)) && (getStartIndex(tmpDividend, newSize) >= 0))
	{
		int tmpStartIndex = getStartIndex(tmpDividend, newSize);
		int i;
		for (i = 0; i < genLen; ++i)
		{
			if((tmpDividend[tmpStartIndex] == 0 && generator[i] == 0) || (tmpDividend[tmpStartIndex] == 1 && generator[i] == 1))
				tmpDividend[tmpStartIndex] = 0;
			else
				tmpDividend[tmpStartIndex] = 1;
			tmpStartIndex++;
		}
	}
	int newStartIndex = getStartIndex(tmpDividend, newSize);
	if(newStartIndex>=0)
	{
		printf("Remainder :\t");
		int i;
		for (i = newStartIndex; i < newSize; ++i)
		{
			printf("%d ", tmpDividend[i]);
		}
		printf("\n");

		//final output

		for (i = 0; i < newSize; ++i)
		{
			if(i>=newStartIndex)
			{
				if((dividend[i] == 0 && tmpDividend[i] == 0) || (dividend[i] == 1 && tmpDividend[i] == 1))
					dividend[i] = 0;
				else
					dividend[i] = 1;
			}
		}
		printf("Final Output :\t");
		for (i = 0; i < newSize; ++i)
		{
			printf("%d ", dividend[i]);
		}
		printf("\n");		
	}
	else
	{
		int i;
		printf("Remainder :\t%d\n",0);
		printf("Final Output :\t");
		for (i = 0; i < newSize; ++i)
		{
			printf("%d ", dividend[i]);
		}
		printf("\n");
	}

}

int getStartIndex(int *tmpDividend, int newSize)
{
	int i;
	for (i = 0; i < newSize; ++i)
	{
		if(tmpDividend[i] == 1)
			break;
	}
	if(i==newSize)
		return -1;
	else
		return i;
}