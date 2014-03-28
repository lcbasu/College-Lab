/* Server code to simulate selective repeat, handles
only one packet drop at a time*/

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

#define MAX_TICKS 5

struct Packet {

	int mInfo;
	int mAck;
	int mType;
}mProduced, Ack;

struct Node {
	int mInfo;
	int mTicks;
	struct Node* mNext;
};

struct LL {
	struct Node* Head;
	int n;
};

struct LL* list;

int InsertNode(int mInfo) {
	struct Node* ptr = malloc(sizeof(struct Node));
	ptr->mInfo = mInfo;
	ptr->mNext = NULL;
	int sum = 0;
	struct Node* curptr = list->Head;
	if(curptr!=NULL) {
		while(curptr != NULL) {
			sum+=curptr->mTicks;
			curptr = curptr->mNext;
		}
		ptr->mTicks = MAX_TICKS - sum;
		curptr = list->Head;
		while(curptr->mNext!=NULL)
			curptr = curptr->mNext;
		curptr->mNext = ptr;
	} else {
		ptr->mTicks = MAX_TICKS;
		list->Head = ptr;
	}
	(list->n)++;
	return list->n;
}

int DeleteNode(int mInfo) {
	if(list->Head==NULL)
		return -1;
	struct Node* prevptr = NULL;
	struct Node* curptr = list->Head;
	while(curptr->mInfo!=mInfo) {
		prevptr = curptr;
		curptr = curptr->mNext;
		if(curptr==NULL)
			return -1;
	}
	int ticks = curptr->mTicks;
	struct Node* temp = curptr->mNext;
	if(temp!=NULL) {
		temp->mTicks+=ticks;
	}
	if(prevptr==NULL)
		list->Head = curptr->mNext;
	else prevptr->mNext = curptr->mNext;
	free(curptr);
	return --(list->n);
}	

int CheckHead() {
	if(list->Head==NULL)
                return -1;
        struct Node* curptr = list->Head;
        curptr->mTicks--;
	if(curptr->mTicks==0)
		return curptr->mInfo;
	return -1;
}

void PrintList() {
	struct Node* ptr = list->Head;
	printf("Timer : ");
	if(ptr == NULL)
		printf("Empty");
	while(ptr!=NULL) {
		printf("%d-%d----",ptr->mInfo,ptr->mTicks);
		ptr = ptr->mNext;
	}
	printf("\n");
	
}

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    int i=0,j, resent;
    struct sockaddr_in serv_addr; 
    int lastsent = 0;
    int recack[1000];
    int lastack = -1;
    char sendBuff[1025];
    list = malloc(sizeof(struct LL));
    list->Head = NULL;
    list->n = 0;

    for(j =0;j<1000;j++)
	recack[j] = 0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    printf("Selective repeat simulation\n");
    while(1)
    {
	printf("Waiting for client...\n");
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
	printf("Connection established with id %d\n",connfd);
	while(1) {
		mProduced.mType=0;
		mProduced.mInfo = lastsent;
		if((resent = CheckHead())>=0) {
			printf("%d timed out!\n", resent);
			mProduced.mInfo = resent;
			DeleteNode(resent);
			lastsent--;
		}
		write(connfd,(void*)&mProduced, 
					sizeof(mProduced));
		DeleteNode(mProduced.mInfo);
		InsertNode(mProduced.mInfo);
		if((i = read(connfd,(void*)&Ack,sizeof(Ack))) > 0) {
			if(Ack.mInfo!=-1) {
				lastack = Ack.mInfo;
				printf("%d ack received\n", lastack);
				DeleteNode(lastack);
				recack[lastack] = 1;
				if(Ack.mType == 1) {
					for(j=0;j<=lastack;j++) {
						recack[j]=1;
						DeleteNode(j);}
					lastsent = lastack;
				}
			}
		}
		else if(i<0)
			printf("Read error!\n");
	       	sleep(1);
		lastsent++;
		PrintList();
	}
	close(connfd);	
     }
}
