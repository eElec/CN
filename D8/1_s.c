// Get info from client 1, and send the data to client 2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

struct Operation{
	int arr[2];
	char operation;
};

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("Usage: ./client <Port>\n");
		return 1;
	}
	const int PORT = atoi(argv[1]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Failed to create socket...\n");
		return 1;
	}
	printf("Socket created successfully.\n");

	int so_reuseaddr = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &so_reuseaddr, sizeof(so_reuseaddr)) < 0
	|| setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(so_reuseaddr)) < 0){	
		printf("Failed to set options.\n");
		return 1;
	}

	struct sockaddr_in srvAddr;
	srvAddr.sin_family = AF_INET;
	srvAddr.sin_port = htons(PORT);
	srvAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int addrlen = sizeof(srvAddr);
	if(bind(sockfd, (struct sockaddr *) &srvAddr, sizeof(srvAddr)) == -1){
		printf("Bind Failed\n");
		return 1;
	}
	printf("Binded to port: %d\n", PORT);

	if(listen(sockfd, 5)!=0){
		printf("Unable to listen.\n");
		return 1;
	}

	int client1fd = accept(sockfd, (struct sockaddr *) &srvAddr, &addrlen);
	int client2fd = accept(sockfd, (struct sockaddr *) &srvAddr, &addrlen);

	char buffer[256];
	struct Operation op;
	int req = recv(client1fd, (struct Operation *) &op, sizeof(op), 0);
	buffer[req] = '\0';
	send(client2fd,  (struct Operation *) &op, sizeof(op), 0);
	
	req = recv(client2fd, (char *) buffer, sizeof(buffer), 0);
	buffer[req] = '\0';
	send(client1fd, (char *) buffer, sizeof(buffer), 0);
}