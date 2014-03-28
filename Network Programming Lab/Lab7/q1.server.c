//help from http://codereview.stackexchange.com/questions/13461/two-way-communication-in-tcp-server-client-implementation

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 3490
#define BACKLOG 10


int checkPalindrome(char *a)
{
	int length = strlen(a)-1;

	int i;

	for(i = 0; i < length/2; i++)
	{
		if(a[i] != a[length-i-1])
		{
			return 0;	//not a palindrome
		}
	}
	return 1;	//is palindrome
}


int main()
{
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int status,socket_fd, client_fd,num;
    socklen_t size;

    char buffer[10241];
    char *buff;
//  memset(buffer,0,sizeof(buffer));
    int yes =1;



    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0))== -1) {
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(&dest,0,sizeof(dest));

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY; 
    
    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr )))== -1)    { //sizeof(struct sockaddr) 
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }

    if ((listen(socket_fd, BACKLOG))== -1){
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }

	while(1) 
	{

        size = sizeof(struct sockaddr_in);

        if ((client_fd = accept(socket_fd, (struct sockaddr *)&dest, &size))==-1 ) 
        {
            perror("accept");
            exit(1);
        }

        while(1) 
        {

                if ((num = recv(client_fd, buffer, 1024,0))== -1) 
                {
                        perror("\trecv");
                        exit(1);
                }
                else if (num == 0) {
                        printf("\tConnection closed\n");
                        //So I can now wait for another client
                        break;
                }
                buffer[num] = '\0';
                printf("Server:\n\tMsg Received %s\n", buffer);

                if(checkPalindrome(buffer) == 1)
                {
                	printf("\tPalindrome\n");
                	buffer[0] = 'y';
                }
                else
                {
                	printf("\tNot a Palindrome\n");
                	buffer[0] = 'n';
                }

                if ((send(client_fd,buffer, strlen(buffer),0))== -1) 
                {
                     fprintf(stderr, "\tFailure Sending Message\n");
                     close(client_fd);
                     break;
                }

        } //End of Inner While...
        //Close Connection Socket
        close(client_fd);
    } //Outer While

    close(socket_fd);
    return 0;
} //End of main