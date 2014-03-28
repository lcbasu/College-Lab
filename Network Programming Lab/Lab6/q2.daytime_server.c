#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define LINE_MAX 100
#define BACKLOG 4
#define MAXBUFLEN 100

int main(int argc, char *argv[])
{
	int listenFd, connFd;

	struct sockaddr_in servAddr;

	char buff[LINE_MAX];

	time_t ticks;

	listenFd = socket(AF_INET, SOCK_STREAM, 0);

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(9999);	//13 is port no for daytime server

	bind(listenFd, (struct sockaddr *)&servAddr, sizeof(servAddr));

	listen(listenFd, BACKLOG);

	while(1)
	{
		connFd = accept(listenFd, (struct sockaddr *)NULL, NULL);
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		write(connFd, buff, strlen(buff));
		close(connFd);
	}

	return 0;
}