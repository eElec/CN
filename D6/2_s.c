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

struct Student{
	int roll;
	int mark1;
	int mark2;
};

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

	struct Student rcvStd;
	int r = recv(recptfd, (struct Student *)&rcvStd, sizeof(rcvStd), 0);
	int temp = rcvStd.mark1;
	rcvStd.mark1 = rcvStd.mark2;
	rcvStd.mark2 = temp;

	send(recptfd, (struct Student *)&rcvStd, sizeof(rcvStd), 0);

	close(recptfd);
	close(sockfd);
}