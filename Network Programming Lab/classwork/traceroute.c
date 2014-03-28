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


struct rec {				/* data in UDP datagram */
  u_short		rec_seq;			
  u_short		rec_ttl;			
  struct timeval	rec_tv;		
};

/* globals */
...
/* function prototypes */
...

struct sockaddr_in  sasend;	/* for send */
struct sockaddr_in  sarecv;	/* for receiving */
struct sockaddr_in  salast;	/* last received */
struct sockaddr_in  sabind;	/* for binding source port */

int		datalen = sizeof(struct rec);	
int		max_ttl = 30;
int		nprobes = 3;
u_short	dport = 32768 + 666;


void send_v4(void)
{
	int		len;
	struct icmp	*icmp;

	icmp = (struct icmp *) sendbuf;
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


void traceloop()
{...

	struct sockaddr_in sabind;
/*   We will recv. ICMP reply on this socket  */

 int recvfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
 setuid(getuid());	/* don't need special permissions any more */


/*   For sending UDP packets   */

 int sendfd = socket(AF_INET, SOCK_DGRAM, 0);

 
/* Kernel will not choose the source port now  */

 bzero(&sabind, sizeof(sabind));
 sabind.sin_family = AF_INET;
 int sport = (getpid() & 0xffff) | 0x8000;    /* our source UDP port# */
 sabind.sin_port = htons(sport);
 bind(sendfd, (struct sockaddr *) &sabind, sizeof(sabind));

/* We will not do anything in signal handler  */ 

 sig_alrm(SIGALRM);
 int seq = 0;	int done = 0;
 
 int ttl;
 for (ttl = 1; ttl <= max_ttl && done == 0; ttl++) {

/* We do not want to build our own IP header  */

	setsockopt(sendfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));
	bzero(&salast, sizeof(salast));

	printf("%2d  ", ttl);
	fflush(stdout);
	int probe;
	for (probe = 0; probe < nprobes; probe++) {
		rec = (struct rec *) sendbuf;
		rec->rec_seq = ++seq;
		rec->rec_ttl = ttl;
		gettimeofday(&rec->rec_tv, NULL);

/* Hopefully this port will not be in use  */

		sasend.sin_port =  htons(dport + seq);
		sendto(sendfd, sendbuf, datalen, 0, 
                    (struct sockaddr *) &sasend, sizeof(sasend));
if ( (code = recv_v4(seq, &tvrecv)) == -3)
	printf(" *");		/* timeout, no reply */
else {

/* Why comparing these two addresses?  */

	if (sock_cmp_addr(&sarecv, &salast, sizeof(sarecv)) != 0) {
		printf(" %s", inet_ntoa(sarecv.sin_addr));
		memcpy(&salast, &sarecv, sizeof(salast));
	}
	tv_sub(&tvrecv, &rec->rec_tv);
	rtt = tvrecv.tv_sec * 1000.0 + tvrecv.tv_usec / 1000.0;
	printf("  %.3f ms", rtt);

	if (code == -1)	/* port unreachable; at destination */
		done++;
	else if (code >= 0)
		printf(" (ICMP %s)", icmpcode_v4(code));
}
fflush(stdout);
}
printf("\n");
}
}



 // Return: 	-3 on timeout
 //	   	-2 on ICMP time exceeded in transit
 //		-1 on ICMP port unreachable (job done)
 //		>= 0 return value is some other ICMP unreachable code

int recv_v4(int seq, struct timeval *tv)
{...
	/*  Setting timeout for recvfrom  */
 alarm(3);
 for ( ; ; ) {
	len = sizeof(struct sockaddr_in);

	/*  Waiting for ICMP message  */
	n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, 
				(struct sockaddr*) &sarecv, &len);
	if (n < 0) {
		if (errno == EINTR)	
			return(-3);	/* alarm expired */
		else	printf("recvfrom error");
	}
	gettimeofday(tv, NULL);	/* get time of packet arrival */

	ip = (struct ip *) recvbuf;	/* start of IP header */
	hlen1 = ip->ip_hl << 2;	/* length of IP header */
	
	icmp = (struct icmp *) (recvbuf + hlen1); /* start of ICMP hdr */
	if ( (icmplen = n - hlen1) < 8)
		printf("icmplen (%d) < 8", icmplen);


/* We hit an intermediate router */

if (icmp->icmp_type == ICMP_TIMXCEED &&
    icmp->icmp_code == ICMP_TIMXCEED_INTRANS) {
    if (icmplen < 8+20+8) 
		printf("icmplen (%d) < 8+20+8", icmplen);

    hip = (struct ip *) (recvbuf + hlen1 + 8);
    hlen2 = hip->ip_hl << 2;
    udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);

    if (hip->ip_p==IPPROTO_UDP && udp->uh_sport == htons(sport) 
			  && udp->uh_dport == htons(dport + seq))
		return(-2);	

} 

		/* have reached destination */

} else if (icmp->icmp_type == ICMP_UNREACH) {
	if (icmplen < 8+20+8) 
			printf("icmplen (%d) < 8+20+8", icmplen);

	hip = (struct ip *) (recvbuf + hlen1 + 8);
	hlen2 = hip->ip_hl << 2;
	udp = (struct udphdr *) (recvbuf + hlen1 + 8 + hlen2);

 	if (hip->ip_p == IPPROTO_UDP &&
		udp->uh_sport == htons(sport) &&
		udp->uh_dport == htons(dport + seq)) {
		if (icmp->icmp_code == ICMP_UNREACH_PORT)
			return(-1);	
		else
			return(icmp->icmp_code);	/* 0, 1, ... */
	}
} /* Some other ICMP error, recvfrom() again */ }

char *icmpcode_v4(int code)
{
  switch (code) {
  case  0:	return("network unreachable");
  case  1:	return("host unreachable");
  case  2:	return("protocol unreachable");
  case  3:	return("port unreachable");
  case  4:	return("fragmentation required but DF bit set");
  case  5:	return("source route failed");
  case  6:	return("destination network unknown");
  case  7:	return("destination host unknown");
  case  8:	return("source host isolated (obsolete)");
  case  9:	return("destination network ...");
  case 10:	return("destination host ...");
  case 11:	return("network unreachable for TOS");
  case 12:	return("host unreachable for TOS");
  case 13:	return("communication ...");
  case 14:	return("host precedence violation");
  case 15:	return("precedence cutoff in effect");
  default:	return("[unknown code]");
  }
}
               



int main(int argc, char **argv)
{
	host = argv[1];
	pid = getpid();
	signal(SIGALRM, sig_alrm);

	printf("traceroute to %s: %d hops max, %d data bytes\n", host,
		   max_ttl, datalen);
	bzero(&sasend, sizeof(sasend));

      /*  This is the address of the destination host   */

	sasend.sin_family = AF_INET;
	sasend.sin_addr.s_addr = inet_addr(argv[1]);

      /*   Where is the port number?   */

	traceloop();

	exit(0);
}

