#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Client Socket not created.\n");
		return;
	}
	printf("Client Socket created.\n");

	// Client Address
	int PORT = 8000;
	char ADDR[] = "127.0.0.1";
	struct sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);
	srvAddr.sin_addr.s_addr = inet_addr(ADDR);

	if(connect(sockfd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1){
		printf("Unable to connect to server on %s:%d\n", ADDR, PORT);
		return;
	}
	printf("Connected to server on %s:%d\n", ADDR, PORT);

	char buffer[256];
	printf("Enter String: ");
	scanf("%[^\n]", buffer);
	send(sockfd, (char *)buffer, sizeof(buffer), 0);
}