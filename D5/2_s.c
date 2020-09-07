// Server - Recieve lower case message, send upper case message

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

void getNumbers(char *buffer, int *arr, int *total){
	char *buff_cpy = buffer;
	// int arr[1024];
	int i = 0;
	int num;
	int skip;
	while(sscanf(buff_cpy, "%d%n", &num, &skip) > 0){
		buff_cpy+=skip;
		arr[i] = num;
		i++;
	}
	*total = i;
}

void main(){
	int sockfd = socket(AF_INET, SOCK_STREAM	, 0);
	if(sockfd == -1){
		printf("Server Socket not created.\n");
		return;
	}
	int so_reuseaddr = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &so_reuseaddr, sizeof(so_reuseaddr)) < 0
	|| setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr, sizeof(so_reuseaddr)) < 0){	
		printf("Failed to set options.\n");
		return;
	}
	printf("Server Socket created successfully\n");

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8000);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int addrlen = sizeof(addr);
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		printf("Bind Failed. ErrNo: %d\n", errno);
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
	int r = recv(recptfd, (char *)buffer, sizeof(buffer), 0);
	buffer[r] = '\0';
	printf("Recieved Number: %s\n", buffer);

	int arr[100];
	int total = 0;
	getNumbers(buffer, arr, &total);

	char resp[256];
	strcpy(resp, "");
	for(int i=0; i<total; i++){
		int isPrime = 1;
		int pmsqrt = sqrt(arr[i]);
		for(int j=2; j<=pmsqrt; j++){
			if(arr[i] % j == 0){
				isPrime = 0;
			}
		}
		if(isPrime){
			char number[10];
			sprintf(number, " %d", arr[i]);
			strcat(resp, number);
		}
	}

	send(recptfd, (char *)resp, sizeof(resp), 0);

	close(recptfd);
	close(sockfd);
}