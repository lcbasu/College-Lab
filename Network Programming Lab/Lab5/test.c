#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
  struct ifreq s;
  int fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
  strcpy(s.ifr_name, "wlan0");

  if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
    int i;
    for (i = 0; i < 6; ++i)
    {
      printf("%02x", (unsigned char) s.ifr_hwaddr.sa_data[i]);
      if(i!=5)
      	printf(":");
    }
    return 0;
  }
  return 1;
}
