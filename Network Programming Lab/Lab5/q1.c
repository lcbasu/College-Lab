/*
Study Materials


#include <sys/socket.h>
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




#include <arpa/inet.h>

const char *inet_ntop(int af, const void *src,
                      char *dst, socklen_t size);

int inet_pton(int af, const char *src, void *dst);

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

#define INET_ADDRSTRLEN     16

int main(int argc, char **argv)
{
    if(argc < 2)
        printf("Require one or more hostname as\n ./a.out <fb.com> <google.com> ...\n");    
    char *ptr, **pptr;
    char str[INET_ADDRSTRLEN];
    struct hostent *hptr;

    while(--argc > 0)
    {
        ptr = *++argv;
        if( (hptr = gethostbyname(ptr)) == NULL)
        {
            printf("Connection Error!\n");
            continue;
        }
        printf("\nOfficial Hostname : %s\n\n", hptr->h_name);

        for(pptr = hptr->h_aliases; *pptr != NULL; pptr++)
            printf("\talias : %s\n", *pptr);
        
        switch(hptr->h_addrtype)
        {
            case AF_INET:
                printf("\tConversion:\n\n");
                for(pptr = hptr->h_addr_list; *pptr != NULL; pptr++)
                {
                    printf("\tPresentation Form :\t%s\t", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
                    int numAddr = 0;
                    inet_pton(hptr->h_addrtype, str, &numAddr);
                    printf("\tByte Form:\t%d\n\n", numAddr);
                }
                break;
            default:
                printf("Unkown address type.\n");
        }
    }
    exit(0);
}