// Client - Send lower case message, recieve upper case message
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Socket not created.\n");
		exit(1);
	}
	struct sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(8000);
	srvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(sockfd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1){
		printf("Unable to connect to server.\n");
		exit(1);
	}

	char buffer[256];
	strcpy(buffer, "");
	printf("Enter Number: ");
	scanf("%[^\n]", buffer);
	send(sockfd, (char *)buffer, sizeof(buffer), 0);

	// Recieve Msg
	recv(sockfd, (char *)buffer, sizeof(buffer), 0);
	printf("Prime Numbers: %s\n", buffer);
	close(sockfd);
}