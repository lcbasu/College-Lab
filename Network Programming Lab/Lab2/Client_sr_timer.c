/* Client : SR without using NAK */

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#define MAX_SIZE 10


struct Packet {
	int mInfo;
	int mAck;
	int mType;
}mReceived,Ack;

int write_helper(int pS, int pI, int pA, int pT) {
	
	Ack.mInfo = pI;
	Ack.mType = pT;
	Ack.mAck = pA;
	write(pS, (void*)&Ack, sizeof(Ack));

}

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0, rbidx = 0;
    struct Packet recvBuff[5];
    struct sockaddr_in serv_addr; 
    int to_be_received = 0;
    int to_be_buffered = 0;
    int lastack = -1,j=0,k=0,flag = 0, flag_ffar = 1;
    char in,i;
    double rand_no = 0;

    srand(time(NULL));
    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    memset(recvBuff, '0',sizeof(recvBuff));
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

    while (1)
    {
	if((n = read(sockfd, &mReceived, sizeof(mReceived))) < 0)
		break;
	//printf("Receive Packet %d?(Y|N)\n",mReceived.mInfo);
        rand_no = rand()/(double)RAND_MAX;
	if(rand_no < 0.8) {
		printf("Received : %d\n",mReceived.mInfo);
		in = 'Y';}
	else {
		in = 'N';
		printf("Dropped : %d\n",mReceived.mInfo);}
	
	//scanf("%s",&in);
	if(in=='Y') {
		if(mReceived.mInfo != to_be_received) {
			flag = 0;
			if(rbidx<MAX_SIZE) {
				for(k = 0; k<rbidx;k++) {
					if(recvBuff[k].mInfo == mReceived.mInfo)
						flag = 1;
				}
				if(!flag && to_be_buffered == mReceived.mInfo) {
					printf("Packet %d buffered\n",mReceived.mInfo);
					recvBuff[rbidx++] = mReceived;
					to_be_buffered = mReceived.mInfo + 1;
					write_helper(sockfd, lastack, 0, 2);
				}
				else {
					printf("Packet %d dropped(duplicate or out of order buffering)!\n", mReceived.mInfo);
					write_helper(sockfd, -1, 0, 3);
				}
			} else {
				printf("Receiver buffer full!\nPacket %d dropped\n",mReceived.mInfo);
				write_helper(sockfd, -1, 0, 3);
			}
		} else {
			printf("%d sent to Network Layer!\n",
						mReceived.mInfo);
			if(rbidx > 0) {
				for(j = 0;j<rbidx;j++)
					printf("%d sent to Network Layer!\n",
							recvBuff[j].mInfo);
				to_be_received = recvBuff[j-1].mInfo;
				rbidx = 0;
			}
			write_helper(sockfd, to_be_received, 0, 1);
			lastack = to_be_received++;
		}
	}
	else {
		printf("Packet %d dropped!\n",mReceived.mInfo);
		write_helper(sockfd, -1, 0, 3);
		if(to_be_received!=mReceived.mInfo) {
			if(rbidx == 0)
				to_be_buffered = mReceived.mInfo;
		} else
			if(rbidx == 0)
				to_be_buffered = mReceived.mInfo + 1;
		
        }

    }

    if(n < 0)
    {
        printf("\n Read error \n");
    } 
    return 0;
}
