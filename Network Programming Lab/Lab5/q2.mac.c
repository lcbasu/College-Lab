#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main() 
{
	struct ifreq src;
	int fdSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	char interfaceName[INET_ADDRSTRLEN] = "eth0";

	memcpy(src.ifr_name, interfaceName, strlen(interfaceName)+1);

	if(!(ioctl(fdSocket, SIOCGIFHWADDR, &src) == 0))
	{
		printf("Connection Error with Interface.\n");
	}
	else
	{
		printf("MAC Address :\t");
		printf("%02x:%02x:%02x:%02x:%02x:%02x",
        (unsigned char)src.ifr_hwaddr.sa_data[0],
        (unsigned char)src.ifr_hwaddr.sa_data[1],
        (unsigned char)src.ifr_hwaddr.sa_data[2],
        (unsigned char)src.ifr_hwaddr.sa_data[3],
        (unsigned char)src.ifr_hwaddr.sa_data[4],
        (unsigned char)src.ifr_hwaddr.sa_data[5]
        );
        printf("\n");
	}
    return 0;
}