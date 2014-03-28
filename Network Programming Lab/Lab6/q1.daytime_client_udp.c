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

int main (int argc,char **argv)
{
	int rcvFdLen;

	socklen_t len;

	char *srvr_addr = NULL;

	struct sockaddr_in adr_srvr;	//AF_INET

	int len_inet;	//length

	int sockFd;	//socket

	struct servent *servntPtr;		//Service entry

	char dateTimeBuff[128];	//Date/Time info

	if(argc >=2)
		srvr_addr = argv[1];	//if in case we want to have command line input
	else
		srvr_addr = "127.0.0.1";	//localhost server

	servntPtr = getservbyname("daytime","udp");	//returns NULL on error
	if(servntPtr == NULL)
		printf("Daytime Server Error\n");

	//Create a server socket address:

	memset(&adr_srvr,0,sizeof(adr_srvr));

	adr_srvr.sin_family = AF_INET;
	adr_srvr.sin_port = (unsigned short)servntPtr->s_port;		//htons(13)
	adr_srvr.sin_addr.s_addr = inet_addr(srvr_addr);

	len_inet = sizeof(adr_srvr);


	//Create a UDP socket to use:

	sockFd = socket(AF_INET,SOCK_DGRAM,0);


	//First send an test message to the server asking for response
	sendto(sockFd, "Test", 0, 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));

	//Fetch the response
	rcvFdLen = recvfrom(sockFd, &dateTimeBuff, sizeof(dateTimeBuff)-1, 0, (struct sockaddr*)&adr_srvr, &len);


	dateTimeBuff[rcvFdLen] = '\0';	//null terminate string

	printf("%s",dateTimeBuff);

	//closing the socket

	close(sockFd);
	return 0;
}