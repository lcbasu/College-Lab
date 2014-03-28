#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h> 


int main ()
{
	int connectFd;
	struct sockaddr_in adr_srvr;
	char *srvr_addr;
	int len_inet;
	int sockFd; 
	char str[1000];	//input string
	int count = 0;

	srvr_addr = "127.0.0.1"; // Use default address
	  
	
	memset(&adr_srvr, 0, sizeof(adr_srvr));

	adr_srvr.sin_family = AF_INET;
	adr_srvr.sin_port = htons(9999);
	adr_srvr.sin_addr.s_addr =inet_addr(srvr_addr);
	
	len_inet = sizeof(adr_srvr);
	

	//creating a TCP/IP socket to use
	sockFd = socket(AF_INET, SOCK_STREAM, 0);

	//connecting to the server:
	connectFd = connect(sockFd, (const struct sockaddr*)&adr_srvr, len_inet);

	if(connectFd == -1)
	{
		printf("Can't connect to server.\n");
	}
	

	//running infinitel unless user types 'stop'
	while(1)
	{
		//take user input
		scanf("%s",str);

		//write the input to the socket
		write(sockFd, str, strlen(str));

		//stopping condition
		if(strcmp(str,"stop") == 0)
			break;

		//reading the output from server
		read(sockFd, str, 1000);

		//checking for palindrome or not
		if(str[0]=='y')
			count++;
	}

	//printing thr total count
	printf("Palindromes: %d\n",count);


	//closing the socket
	close(sockFd);

	printf("\n");
	return 0;
}









