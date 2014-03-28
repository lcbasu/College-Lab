#include <iostream>
#include "kbhit.h"
using namespace std;
int main()
{
int ch = 0;
init_keyboard();
while(ch != 'q') {
	printf("looping");
	sleep(1);
	if(kbhit()) {
		ch = readch();
	printf("you hit %c\n",ch);
	}
}
close_keyboard();
exit(0);
}
