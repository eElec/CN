#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(int argc, char* argv[]){
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		printf("Server Socket not created.\n");
		return;
	}
	printf("Server Socket created successfully\n");

	struct sockaddr_in addr, src_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		printf("Bind Failed\n");
		return;
	}
	printf("Bind Successful\n");

	char buffer[100];
	src_addr.sin_family = AF_INET;
	src_addr.sin_port = htons(8081);
	src_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	socklen_t addrlen = sizeof(src_addr);

	while(strcmp(buffer, "exit") != 0){
		int r = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addrlen);
		
		if(r == -1){
			printf("Recieve Error.\n");
			return;
		}

		printf("Recieved String: %s\n", buffer);
		buffer[r] = '\0';

		char str[100];
		if(strcmp(buffer, "Hello") == 0){
			strcpy(str, "Hello Client");
		}
		else if(strcmp(buffer, "Hows CN Lab") == 0){
			strcpy(str, "Cool");
		}
		else if(strcmp(buffer, "exit") == 0){
			strcpy(str, "Bye");
		}
		else{
			strcpy(str, "Recieved");
		}
		int serr = sendto(sockfd, (char *)str, sizeof(str), 0, (struct sockaddr *) &src_addr, sizeof(src_addr));
	}
	close(sockfd);
}