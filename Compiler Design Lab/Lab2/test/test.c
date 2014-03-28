#include <stdio.h>
#include <string.h>

char *ID_TABLE[100];
int total_id = 0;
void exchange(char *s, char *d);
void quicksort(char *arr, int p, int r);
int partition(char *arr, int p, int r);

int installID(char *id)
{
	if(total_id > 0)
	{
		int i;
		for(i=0; i<=total_id; i++)
		{
			if(ID_TABLE[i] == id)
				return i;
		}

	}
	ID_TABLE[total_id] = id;
	total_id = total_id + 1;
	return (total_id-1);
}

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

	int a = installID("WARDAN");

	int b = installID("WARDAN");

	int c = installID("WARDAN C BASU");	

	char arr[] = "hello";

	quicksort(arr, 0, 3);

	int i;
	for (i = 0; i < 5; ++i)
	{
		printf("%c\n", arr[i]);
	}


	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	return 0;
}