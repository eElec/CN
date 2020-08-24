#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int LCM(int a, int b) 
{ 
	int max = (a > b) ? a : b;
	int min = (a < b) ? a : b;
	for (int i = max; ; i += max) { 
        if (i % min == 0) 
            return i; 
    } 
} 

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

	int r = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addrlen);
	if(r == -1){
		printf("Recieve Error.\n");
		return;
	}
	buffer[r] = '\0';
	printf("Number 1: %s\n", buffer);
	int num1 = atoi(buffer);

	r = recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&src_addr, &addrlen);
	if(r == -1){
		printf("Recieve Error.\n");
		return;
	}
	buffer[r] = '\0';
	printf("Number 2: %s\n", buffer);
	int num2 = atoi(buffer);

	int lcm = LCM(num1, num2);
	char str[100];
	printf("GCD: %d\n", lcm);
	sprintf(str, "%d", lcm);
	int serr = sendto(sockfd, (char *)str, sizeof(str), 0, (struct sockaddr *) &src_addr, sizeof(src_addr));

	close(sockfd);
}