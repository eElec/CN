#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void main(int argc, char* argv[]){
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		printf("Client Socket not created.\n");
		return;
	}
	printf("Client Socket created successfully\n");

	struct sockaddr_in addr, dest_addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8081);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		printf("Bind Failed\n");
		return;
	}
	printf("Bind Successful\n");

	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(8080);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	char buffer[100];
	while(strcmp(buffer, "Bye")){
		char str[100];
		printf("Enter String: ");
		scanf("%[^\n]%*c", str);

		int serr = sendto(sockfd, (char *)str, sizeof(str), 0, (struct sockaddr *) &dest_addr, sizeof(dest_addr));
		if(serr == -1){
			printf("Message not sent.\n");
			return;
		}

		socklen_t addrlen = sizeof(dest_addr);

		int r = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&dest_addr, &addrlen);
		if(r == -1){
			printf("Recieve Error.\n");
			return;
		}
		buffer[r] = '\0';
		printf("Recieved: %s\n", buffer);
	}
	close(sockfd);
}