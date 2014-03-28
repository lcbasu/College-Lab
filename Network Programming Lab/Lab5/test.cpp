#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

int main()
{
  struct ifreq s;
  int fd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
  strcpy(s.ifr_name, "wlan0");

  if (0 == ioctl(fd, SIOCGIFHWADDR, &s)) {
    int i;
    for (i = 0; i < 6; ++i)
      printf(" %02x", (unsigned char) s.ifr_hwaddr.sa_data[i]);
    puts("\n");

    cout << s.ifr_hwaddr.sa_data << endl;

    return 0;
  }
  return 1;
}
