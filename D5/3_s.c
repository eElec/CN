// Server - Recieve lower case message, send upper case message

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(){
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Server Socket not created.\n");
		return;
	}
	printf("Server Socket created successfully\n");

	int so_reuseaddr = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &so_reuseaddr, sizeof(so_reuseaddr)) < 0
	|| setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(so_reuseaddr)) < 0){	
		printf("Failed to set options.\n");
		return;
	}
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int addrlen = sizeof(addr);
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		printf("Bind Failed\n");
		return;
	}
	printf("Bind Successful\n");

	if(listen(sockfd, 5)!=0){
		printf("Unable to listen.\n");
		return;
	};

	int recptfd = accept(sockfd, (struct sockaddr *) &addr, &addrlen);
	if(recptfd == -1){
		printf("Accept failed.\n");
		return;
	}

	char buffer[256];	
	char response[256];
	while(strcasecmp(buffer, "exit") != 0){
		int r = recv(recptfd, (char *)buffer, sizeof(buffer), 0);
		buffer[r] = '\0';
		printf("Recieved String: %s\n", buffer);

		if(strcasecmp(buffer, "exit") == 0){
			strcpy(response, "Good Bye!");
		}
		else if(strcasecmp(buffer, "hi") == 0){
			strcpy(response, "Hello!");
		}
		else{
			strcpy(response, buffer);
		}

		send(recptfd, (char *)response, sizeof(response), 0);
	}

	close(recptfd);
	close(sockfd);
}