
//	netinet/in.h
//	IPPROTO_IP              0               /* dummy for IP */
//	IPPROTO_UDP             17              /* user datagram protocol */
//	IPPROTO_TCP             6               /* tcp */


#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <netinet/in.h>


int main() 
{
	int sndBuffSize, recvBuffSize;

	//get buffer size
	socklen_t buffLen;

	//socket descriptor
	int fdsocketUDP, fdsocketTCP;


	//UDP

	//receive buffer calculation
	buffLen = sizeof(recvBuffSize);
	fdsocketUDP = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	getsockopt(fdsocketUDP,SOL_SOCKET,SO_RCVBUF,(void *)&recvBuffSize, &buffLen);
	// now the variable recvBuffSize will have the socket size
	printf("UDP Receive Buffer Size:\t%d\n", recvBuffSize);


	//send buffer calculation
	buffLen = sizeof(sndBuffSize);

	getsockopt(fdsocketUDP,SOL_SOCKET,SO_SNDBUF,(void *)&sndBuffSize, &buffLen);
	// now the variable sndBuffSize will have the socket size
	printf("UDP Send Buffer Size:\t\t%d\n", sndBuffSize);	



	//TCP

	//receive buffer calculation
	buffLen = sizeof(recvBuffSize);
	fdsocketTCP = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	getsockopt(fdsocketTCP,SOL_SOCKET,SO_RCVBUF,(void *)&recvBuffSize, &buffLen);
	// now the variable recvBuffSize will have the socket size
	printf("TCP Receive Buffer Size:\t%d\n", recvBuffSize);


	//send buffer calculation
	buffLen = sizeof(sndBuffSize);

	getsockopt(fdsocketTCP,SOL_SOCKET,SO_SNDBUF,(void *)&sndBuffSize, &buffLen);
	// now the variable sndBuffSize will have the socket size
	printf("TCP Send Buffer Size:\t\t%d\n", sndBuffSize);		



	printf("\n\n");

	// Set buffer size	

	//UDP

	sndBuffSize = 4496;
	recvBuffSize = 4496;

	printf("Sets the send buffer to :\t%d\n", sndBuffSize);
	printf("Sets the receive buffer to :\t%d\n", sndBuffSize);
	printf("\n");

	setsockopt(fdsocketUDP, SOL_SOCKET, SO_SNDBUF, &sndBuffSize, buffLen);
	setsockopt(fdsocketUDP, SOL_SOCKET, SO_RCVBUF, &recvBuffSize, buffLen);

	//receive buffer size calculation
	buffLen = sizeof(recvBuffSize);

	getsockopt(fdsocketUDP,SOL_SOCKET,SO_RCVBUF,(void *)&recvBuffSize, &buffLen);
	// now the variable recvBuffSize will have the socket size
	printf("UDP Receive Buffer Size:\t%d\n", recvBuffSize);


	//send buffer calculation
	buffLen = sizeof(sndBuffSize);

	getsockopt(fdsocketUDP,SOL_SOCKET,SO_SNDBUF,(void *)&sndBuffSize, &buffLen);
	// now the variable sndBuffSize will have the socket size
	printf("UDP Send Buffer Size:\t\t%d\n", sndBuffSize);	


	printf("\n\n");
	
	//TCP

	setsockopt(fdsocketTCP, SOL_SOCKET, SO_SNDBUF, &sndBuffSize, buffLen);
	setsockopt(fdsocketTCP, SOL_SOCKET, SO_RCVBUF, &recvBuffSize, buffLen);

	//receive buffer size calculation
	buffLen = sizeof(recvBuffSize);

	getsockopt(fdsocketTCP,SOL_SOCKET,SO_RCVBUF,(void *)&recvBuffSize, &buffLen);
	// now the variable recvBuffSize will have the socket size
	printf("TCP Receive Buffer Size:\t%d\n", recvBuffSize);


	//send buffer calculation
	buffLen = sizeof(sndBuffSize);

	getsockopt(fdsocketTCP,SOL_SOCKET,SO_SNDBUF,(void *)&sndBuffSize, &buffLen);
	// now the variable sndBuffSize will have the socket size
	printf("TCP Send Buffer Size:\t\t%d\n", sndBuffSize);		


	return 0;
}