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
	int z;

	char *srvr_addr = NULL;

	struct sockaddr_in adr_srvr;	//AF_INET

	int len_inet;	//length

	int s;	//socket

	struct servent *sp;		//Service entry

	char dateTimeBuff[128];	//Date/Time info

	if(argc >=2)
		srvr_addr = argv[1];	//if in case we want to have command line input
	else
		srvr_addr = "127.0.0.1";	//localhost server

	sp = getservbyname("daytime","tcp");	//returns NULL on error
	if(sp == NULL)
		printf("Daytime Server Error\n");

	//Create a server socket address:

	memset(&adr_srvr,0,sizeof(adr_srvr));

	adr_srvr.sin_family = AF_INET;

	//to test htons(9999)
	adr_srvr.sin_port = htons(9999);		//htons(13)
	adr_srvr.sin_addr.s_addr = inet_addr(srvr_addr);

	len_inet = sizeof(adr_srvr);


	//Create a TCP/IP socket to use:

	s = socket(AF_INET,SOCK_STREAM,0);


	//Connect to the server:

	z = connect(s,(const struct sockaddr*)&adr_srvr, sizeof(adr_srvr));

	//Read the date/time info

	z = read(s, dateTimeBuff, sizeof(dateTimeBuff)-1);
	dateTimeBuff[z] = '\0';	//null terminate string

	printf("%s",dateTimeBuff);

	//closing the socket

	close(s);
	printf("\n");
	return 0;
}