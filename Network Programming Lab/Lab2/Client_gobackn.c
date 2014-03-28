#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h> 

struct Packet {
	int mInfo;
	int mAck;
	int mType;
	int mTS;
}mReceived,Ack;


int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    struct sockaddr_in serv_addr; 
    int to_be_received = 0;
    int lastack = -1,i=0,j=0,received = 0, dropped = 0, total=0, timer = 0;
    FILE* file;
    double delay[100],avg_delay = 0,rand_no ,avg_pl=0;
    char in;

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
    for(i=0;i<100;i++)
	delay[i]=0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
 
    srand(time(NULL));
    while (1)
    {
	if((n = read(sockfd, &mReceived, sizeof(mReceived))) < 0)
		break;
	//printf("Receive Packet %d?(Y|N)\n",mReceived.mInfo);
	//scanf("%s",&in);
	
	rand_no = rand()/(double)RAND_MAX;
	if(rand_no < 0.8) {
		printf("Received : %d\n",mReceived.mInfo);
		in = 'Y';
		received++;
	} else {
		in = 'N';
		printf("Dropped : %d\n",mReceived.mInfo);
		dropped++;	
	}
	if(in=='Y') {
		if(mReceived.mInfo != to_be_received) {
			printf("Packet %d Dropped\n",mReceived.mInfo);
			Ack.mInfo = -1;
			Ack.mType = 3;
			write(sockfd, (void*)&Ack, sizeof(Ack));
		}else {
			printf("%d sent to Network Layer!\n",
						mReceived.mInfo);
			delay[mReceived.mInfo] = (timer - mReceived.mTS)*0.2 + 0.1;
               		Ack.mInfo = to_be_received;
			Ack.mType = 1;
			write(sockfd,(void*)&Ack, sizeof(Ack));
			lastack = to_be_received++;
		}
	}
	else {
		Ack.mInfo = -1;
                Ack.mType = 3;
                write(sockfd,(void*)&Ack, sizeof(Ack));
        }
    timer++;
    total++;
    if(to_be_received>=10)
	break;
    }

    if(n < 0)
        printf("\n Read error \n");
    for(j=0;j<100;j++)
	avg_delay+=delay[j];
    avg_delay = avg_delay/lastack;
    avg_pl = dropped/(double)total;
    printf("Perc packet lost : %f\nAvg packet delay : %f\n",avg_pl,avg_delay);
    file = fopen("results.txt", "a");
    fprintf(file, "%f %f\n", avg_pl, avg_delay);
    return 0;
}
