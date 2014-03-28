#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

struct Packet {

	int mInfo;
	int mAck;
	int mType;
        int mTS;
}mProduced, Ack;

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    int i=0,j;
    struct sockaddr_in serv_addr; 
    int lastsent = 0;
    int recack[100];
    int lastack = -1;
    char sendBuff[1025];
    int time_stamps[100];
    int timer = 0;
    
    for(j =0;j<100;j++){
	recack[j] = 0;
	time_stamps[j] = -1;
    }

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    printf("Go back n simulation\n");
    while(1)
    {
	printf("Waiting for client...\n");
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
	printf("Connection established with id %d\n",connfd);
	while(1) {
		mProduced.mType=0;
		mProduced.mInfo = lastsent;
		if(time_stamps[mProduced.mInfo]==-1) {
			mProduced.mTS = timer;
			time_stamps[mProduced.mInfo] = mProduced.mTS;
		}
		else
			mProduced.mTS = time_stamps[mProduced.mInfo];
		write(connfd,(void*)&mProduced, sizeof(mProduced)); 
		if((i = read(connfd,(void*)&Ack,sizeof(Ack))) > 0) {
			if(Ack.mInfo!=-1){
				lastack = Ack.mInfo;
				printf("%d ack received\n", lastack);
				recack[lastack] = 1;
			}
		}
		if(lastsent-3 >= 0)
			if(!recack[lastsent-3]) { 
				lastsent = lastsent-4;
				printf("%d timed out\n", lastsent+1);
			}
        	sleep(1);
		lastsent++;
	}
	close(connfd);	
     }
}

