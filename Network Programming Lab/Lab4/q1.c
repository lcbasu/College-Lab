#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t usr_interrupt1 = 0;
volatile sig_atomic_t usr_interrupt2 = 0;

void printPID(int sig)
{
  usr_interrupt1=1;
}

void makeChildren(int sig)
{
	usr_interrupt2=1;
}

void parentSignal(int sig)
{
	int i=0;
	i=i+1;
}
/* The child process executes this function.  */
void child_function (void)
{

	struct sigaction usr_action1;
	sigset_t block_mask,zero1;
	pid_t child_pid1, child_pid2;

	/* Establish the signal handler.  */
	sigfillset (&block_mask);
	usr_action1.sa_handler = printPID;
	usr_action1.sa_mask = block_mask;
	usr_action1.sa_flags = 0;
	sigaction (SIGUSR1, &usr_action1, NULL);

	struct sigaction usr_action2;
	usr_action2.sa_handler = makeChildren;
	usr_action2.sa_mask = block_mask;
	usr_action2.sa_flags = 0;
	sigaction (SIGUSR2, &usr_action2, NULL);
	

	sigemptyset(&zero1);
	sigsuspend(&zero1);
	
	if(usr_interrupt1==1)
	{
		printf("\tChild pid:%d ppid:%d\n",getpid(),getppid());
		kill(getppid(),SIGUSR1);
	}
	else
		printf("Something wrong\n");
	
	sigsuspend(&zero1);
	
	if(usr_interrupt2==1)
	{	
	
		pid_t pid_grand1, pid_grand2;;

		if((pid_grand1=fork()) < 0)
		{
		    printf("Something is wrong!!\n");
		}
		else if(pid_grand1 == 0)
		{
		     printf("\t\tGrandChild pid:%d  ppid:%d\n", getpid(),getppid());
			 kill(getppid(),SIGUSR1);
			exit(0);
		}
		else
		{
			sigsuspend(&zero1);
			
			if((pid_grand2 = fork()) < 0)
			{
				printf("Something is wrong!!\n");
			}
			else if(pid_grand2 == 0)
			{
				 printf("\t\tGrandChild pid:%d  ppid:%d\n", getpid(),getppid());
				 kill(getppid(),SIGUSR1);
				 exit(0);
			}
			else
			{
				sigsuspend(&zero1);
			}

		}
		     
	}
	wait();
	wait();
    exit (0);
}


int main (void)
{
	struct sigaction usr_action;
	sigset_t block_mask;
	sigset_t zero,waitmask;
	sigemptyset(&zero);
	pid_t pid1,pid2;

	sigaddset(&waitmask,SIGUSR1);
	sigaddset(&waitmask,SIGUSR2);
	sigfillset(&block_mask);

	sigprocmask(SIG_SETMASK,&waitmask,NULL);

	printf("Parent pid:%d ppid:%d\n",getpid(),getppid());

	/* Create the child process.  */
	if((pid1 = fork()) < 0)
	{
		printf("fork() error \n");
		exit(0);
	}
	//Child 1 Code
	else if(pid1==0)
	{
		/* Call the child function  */
		child_function();	
		exit(0);
	}
	else
	{
		if((pid2 = fork()) < 0)
		{
			printf("fork() error\n");
			exit(0);
		}
		else if(pid2==0)
        {
			child_function();	
			exit(0);	
		}
             else
		{
 			sigfillset (&block_mask);
			usr_action.sa_handler = parentSignal;
			usr_action.sa_mask = block_mask;
			usr_action.sa_flags = 0;
			sigaction (SIGUSR1, &usr_action, NULL);


                       
         	kill (pid1, SIGUSR1);
			sigsuspend(&zero);
			kill (pid2,SIGUSR1);
            sigsuspend(&zero);
			kill(pid1,SIGUSR2);
			kill(pid2,SIGUSR2);
			
			/* Wait for both the children to die */
			wait();
			wait();
			sleep(1);
			
		}
		
  }
  return 0;
}
