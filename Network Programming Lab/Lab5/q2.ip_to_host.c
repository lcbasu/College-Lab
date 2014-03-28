/*
Study Materials

struct hostent 
{
/*       char    *h_name;        /* official name of host */
/*       char    **h_aliases;    /* alias list */
/*        int     h_addrtype;     /* host address type */
/*        int     h_length;       /* length of address */
/*        char    **h_addr_list;  /* list of addresses */
/* } */




/*


#include <sys/socket.h>
#include <netdb.h>

struct hostent *gethostbyname(const char *name); // DEPRECATED!
struct hostent *gethostbyaddr(const char *addr, int len, int type);

struct in_addr {
        unsigned long int s_addr;
}


*/
//*/


#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define	INET_ADDRSTRLEN		16

int main(int argc, char **argv)
{
	if(argc < 2)
		printf("Require one or more ip address as\n ./a.out <ipAddress1> ...\n");
	char *ptr, **pptr;
	char str[INET_ADDRSTRLEN];
	struct hostent *hptr;

	in_addr_t ip;
	struct in_addr ip_addr;	

	while(--argc > 0)
	{
		ptr = *++argv;	//getting the pointer to the ip address

		ip = inet_addr(ptr);	//converts the ip addr from numbers-and-dots notation into binary data in network byte order.

		ip_addr.s_addr = ip;

		if( (hptr = gethostbyaddr(&ip_addr, sizeof(ip_addr), AF_INET)) == NULL)
		{
			printf("Connection Error!\n");
			continue;
		}
		printf("\nOfficial Hostname : %s\n", hptr->h_name);

		for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
			printf("\talias : %s\n", *pptr);
		
		switch(hptr->h_addrtype)
		{
			case AF_INET:
				for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
					printf("\taddress: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
				break;
			default:
				printf("Unkown address type.\n");
		}
	}
	exit(0);
}