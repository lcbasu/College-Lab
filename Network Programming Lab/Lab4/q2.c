#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>

void quicksort(int [],int,int);
int partition (int [],int,int,int);

int main(void) {
	int fd1[2],fd2[2];
	int i;
	pid_t pid;
	if(pipe(fd1)!=0){
		printf("Pipe Error\n");
		exit(0);
	}
	if(pipe(fd2)!=0){
		printf("Pipe Error\n");
		exit(0);
	}

	if((pid=fork())==0){
		//Inside Server
		int length;
		int *arr;
		close(fd1[1]);
		close(fd2[0]);

		read(fd1[0],(char*)&length,sizeof(int));
		printf("Server: Length of array: %d\n",length);
		arr=(int*)calloc(length,sizeof(int));

		for(i=0;i<length;i++){
			read(fd1[0],(char*)&(arr[i]),sizeof(int));
			printf("Server: Integer %d : %d\n",i,arr[i]);
		}

		quicksort(arr,0,length-1);

		printf("Server: Sorted and sending array to client\n");

		for(i=0;i<length;i++){
			write(fd2[1],(char*)&(arr[i]),sizeof(int));
		}

		close(fd1[0]);
		close(fd2[1]);

	}
	else {
		//Inside Client
		int a[10]={4,2,8,6,5,9,1,13,11,7};
		int sorted[10];
		int length=10;
		close(fd1[0]);
		close(fd2[1]);

		write(fd1[1],(char*)&length,sizeof(int));

		printf("Client: Sending array to Server for sorting \n");

		for(i=0;i<length;i++){
			write(fd1[1],(char*)&(a[i]),sizeof(int));
		}

		for(i=0;i<length;i++){
			read(fd2[0],(char*)&(sorted[i]),sizeof(int));
			printf("Client: Integer %d : %d\n",i,sorted[i]);
		}

		close(fd1[1]);
		close(fd2[0]);

	}

	return EXIT_SUCCESS;
}

void quicksort(int a[],int left,int right){
	if (left<right){
		int pivotIndex=(left+right)/2;
		int pivotNewIndex=partition(a,left,right,pivotIndex);
		quicksort(a,left,pivotNewIndex-1);
		quicksort(a,pivotNewIndex+1,right);
	}
}

int partition (int a[],int left,int right,int pivot){
	int pivotValue=a[pivot];
	int temp=pivotValue;
	int storeIndex=left;
	int i;
	a[pivot]=a[right];
	a[right]=temp;


	for (i=left;i<right;i++){
		if(a[i]<pivotValue){
			temp=a[i];
			a[i]=a[storeIndex];
			a[storeIndex]=temp;
			storeIndex++;
		}
	}
	temp=a[storeIndex];
	a[storeIndex]=a[right];
	a[right]=temp;
	return storeIndex;
}
