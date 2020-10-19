/* Write a program to send an integer array to the server from client, then server will swap the
 * consecutive even numbers present in the array and display the resultant array in the client using
 * TCP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

struct Arr{
	int arr[50];
	int size;
};

void main(int argc, char* argv[]){
	if(argc < 2){
		printf("Usage: ./client <Port>\n");
		return;
	}
	const int PORT = atoi(argv[1]);
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
	addr.sin_port = htons(PORT);
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

	struct Arr arr;
	int r = recv(recptfd, (struct Arr *) &arr, sizeof(arr), 0);
	
	int m = -1, n = -1;
	for(int i=0; i<arr.size; i++){
		if(arr.arr[i]%2 == 0){
			if(m == -1){
				m = i;
			}
			else{
				n = i;
				int temp = arr.arr[n];
				arr.arr[n] = arr.arr[m];
				arr.arr[m] = temp;
				m = -1, n = -1;
			}
		}
	}

	send(recptfd, (struct Arr *) &arr, sizeof(arr), 0);

	close(recptfd);
	close(sockfd);
}