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


#define BACKLOG 20

int checkPalindrome(char []);

int main(int argc, char *argv[])
{
	size_t addr_len;

	int portNumber=9999;

	int sockFd;

	int cli_sfd;

	char buff[1000];

	int result;

	int n;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

	if ((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket error\n");
		return 1;
	}
	
	

	//preparing the server address struct
	server_addr.sin_family      = AF_INET;
	server_addr.sin_port        = htons(portNumber);

	//listening to all interfaces
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	memset(&(server_addr.sin_zero), '\0', 8);
	
	//associating the socket with a port number using bind()
	if (bind(sockFd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("bind error\n");
		return 2;
	}


	listen(sockFd,BACKLOG);

	

	while(1)
	{	
		cli_sfd = accept(sockFd, (struct sockaddr*)&client_addr, &addr_len);
		
		n = read(cli_sfd, buff, 1000);

		buff[n]='\0';

		if(strcmp(buff,"stop")==0)
			break;

		result = checkPalindrome(buff);

		if(result == 0)
			buff[0] = 'n';
		else
			buff[0] = 'y';

		n = write(cli_sfd,buff,1);
	
	}

	//closing the socket descriptors
	close(sockFd);
	close(cli_sfd);	
	
}

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
