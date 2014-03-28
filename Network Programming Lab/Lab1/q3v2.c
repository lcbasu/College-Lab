#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void forkChild(int noOfChildren);
void forkGrandChild(int noOfGrandChildren, int child);

void forkChild(int noOfChildren)
{
	pid_t pid;
	int i;
	for (i = 0; i < noOfChildren; ++i)
	{
		pid = fork();
		if(pid == -1)
			return;
		else if(pid == 0)
		{
			printf("Child Process %d with pid %d.\n", i, getpid());
			forkGrandChild(2, i);
			//sleep(noOfChildren);
			return;
		}
	}
}

void forkGrandChild(int noOfGrandChildren, int child)
{
	pid_t pid;
	int i;
	for (i = 0; i < noOfGrandChildren; ++i)
	{
		pid = fork();
		if(pid == -1)
			return;
		else if(pid == 0)
		{
			printf("Grand Child Process %d of Child %d with pid %d.\n", i, child, getpid());
			//sleep(noOfGrandChildren);
			return;
		}
	}
}

int main()
{
	printf("PID of parent is :\t%d\n", getpid());
	forkChild(2);

	return 0;
}