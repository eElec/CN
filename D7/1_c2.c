#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(int argc, char* argv[]){
	if(argc < 2){
		printf("Usage: ./client <Port>\n");
		return;
	}
	const int PORT = atoi(argv[1]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Socket not created.\n");
		exit(1);
	}
	struct sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);
	srvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	if(connect(sockfd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1){
		printf("Unable to connect to server.\n");
		exit(1);
	}

	char buffer[256];
	strcpy(buffer, "");
	recv(sockfd, (char *)buffer, sizeof(buffer), 0);
	printf("Recieved Message: %s\n", buffer);
	close(sockfd);
}