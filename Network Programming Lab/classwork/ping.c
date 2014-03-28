#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <sys/un.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define MAX 1000

int	datalen = 56;		/* data that goes with ICMP echo request */


char recvbuf[MAX];
char sendbuf[MAX];

void readloop(char *host)
{
	struct sockaddr_in sarecv;
	int sockfd = socket(AF_INET,  SOCK_RAW,  IPPROTO_ICMP);
	setuid(getuid());	/* don't need special permissions any more */

	sig_alrm(SIGALRM);		/* send first packet */

	struct timeval *tval;

	for ( ; ; ) 
	{
		size_t size = sizeof(sarecv);
		int n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, (struct sockaddr*) &sarecv, &size);
		if (n < 0)
		{
			printf("recvfrom error");
		}
		gettimeofday(&tval, NULL);
		proc_v4(recvbuf, n, &tval, host);
	}
}

void send_v4(void)
{

	struct sockaddr_in sasend;

	int		len;
	struct icmp	*icmp;

	pid_t pid = getpid();

	icmp = (struct icmp *)sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = pid;
	icmp->icmp_seq = nsent++;
	gettimeofday((struct timeval *) icmp->icmp_data, NULL);

	len = 8 + datalen;		/* checksum ICMP header and data */
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum((u_short *) icmp, len);

	sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) &sasend,sizeof(sasend));
}

void sig_alrm(int signo)
{
	send_v4();
	alarm(1);
	return;		/* probably interrupts recvfrom() */
}


void  proc_v4(char *ptr, ssize_t len, struct timeval *tvrecv, char *host)
{	…

	struct icmp	*icmp;
	ip = (struct ip *) ptr;		/* start of IP header */
	hlen1 = ip->ip_hl << 2;		/* length of IP header */

	icmp = (struct icmp *) (ptr + hlen1);	/* start of ICMP header */
	int icmplen;
	if ( (icmplen = len - hlen1) < 8)
		printf("icmplen (%d) < 8", icmplen);

	if (icmp->icmp_type == ICMP_ECHOREPLY) {
		if (icmp->icmp_id != pid)
			return;		/* not a response to our ECHO_REQUEST */
		if (icmplen < 16)
			printf("icmplen (%d) < 16", icmplen);

		tvsend = (struct timeval *) icmp->icmp_data;
		tv_sub(tvrecv, tvsend);
		float rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;

		printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
				icmplen, host,icmp->icmp_seq, ip->ip_ttl, rtt);
	} 
}

int main(int argc, char **argv)
{
	struct sockaddr_in sasend;
	char *host = argv[1];
	int pid = getpid();
	signal(SIGALRM, sig_alrm);

	printf("PING %s : %d data bytes\n", argv[1], datalen);

	bzero(&sasend, sizeof(sasend));
	sasend.sin_family = AF_INET;
	sasend.sin_addr.s_addr = inet_addr(argv[1]);
	
	readloop(argv[1]);
	exit(0);
}
