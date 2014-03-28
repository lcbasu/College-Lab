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

/*
* This function reports the error and
* exits back to the shell:
*/
static void displayError (const char *on_what) {
	printf("Error: %s",on_what);
	exit (1);
}

int main (int argc,char **argv) {
	int z,len;
	char *srvr_addr = NULL;
	struct sockaddr_in adr_srvr;/* AF_INET */
	int len_inet; /* length */
	int s; /* Socket */
	struct servent *sp; /* Service entry */
	char dtbuf[128]; /* Date/Time info */
	
	if ( argc >= 2 ) {
		srvr_addr = argv[1]; // Addr on cmdline
	} 
	else {
		srvr_addr = "127.0.0.1"; // Use default address
	}
	  
	/*
	* Lookup the daytime tcp service:
	*/
	sp = getservbyname("daytime","tcp");
	if ( !sp ) {
		fputs("Unknown service: daytime tcp\n", stderr);
		exit(1);
	}
	/*
	* Create a server socket address:
	*/
	memset(&adr_srvr,0,sizeof adr_srvr);
	adr_srvr.sin_family = AF_INET;
	adr_srvr.sin_port = (unsigned short)sp->s_port; //htons(13)
	adr_srvr.sin_addr.s_addr =
	inet_addr(srvr_addr);
	
	if ( adr_srvr.sin_addr.s_addr == INADDR_NONE ) {
		displayError ("bad address.");
	}
	len_inet = sizeof adr_srvr;
	
	/*
	* Create a TCP/IP socket to use:
	*/
	s = socket(AF_INET,SOCK_DGRAM,0);
	if ( s == -1 ) {
		displayError("socket()");
	}
	
	
	/*
	* Read the date/time info:
	*/
	
	//First send an empty message to the server asking for response
	sendto(s, "", 0, 0, (struct sockaddr *)&adr_srvr, sizeof(adr_srvr));
	
	//Fetch the response
	z=recvfrom(s,&dtbuf,sizeof(dtbuf)-1,0,(struct sockaddr*)&adr_srvr,&len);
	if ( z == -1 ) {
		displayError("read(2)");
	}
	
	/*
	* Report the Date & Time:
	*/
	dtbuf[z] = 0; /* null terminate string */
	printf("Date & Time is: %s\n",dtbuf);
	
	
	/*
	* Close the socket and exit:
	*/
	close(s);
	putchar('\n');
	return 0;
}
