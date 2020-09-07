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
	char name[20];
	float cgpa;
};

void populateStudent(struct Student *std){
	std[0].roll = 1806188;
	strcpy(std[0].name, "Adrish");
	std[0].cgpa = 8.8;

	std[1].roll = 1806189;
	strcpy(std[1].name, "Akash");
	std[1].cgpa = 8.9;

	std[2].roll = 1806190;
	strcpy(std[2].name, "Akshat");
	std[2].cgpa = 9.5;
	
	std[3].roll = 1806203;
	strcpy(std[3].name, "Atul");
	std[3].cgpa = 8.9;

	std[4].roll = 1806204;
	strcpy(std[4].name, "Ayan");
	std[4].cgpa = 8.8;
}

void main(){
	struct Student std[5];
	populateStudent(std);
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
	int r = recv(recptfd, (char *)buffer, sizeof(buffer), 0);
	buffer[r] = '\0';
	printf("Recieved Roll Number: %s\n", buffer);
	int roll = atoi(buffer);

	char response[256];
	for(int i=0; i<5; i++){
		if(roll == std[i].roll){
			sprintf(response, "Roll: %d\nName: %s\nCGPA: %.2f", std[i].roll, std[i].name, std[i].cgpa);
			break;
		}
	}
	printf("%s, %d\n", response, roll);

	send(recptfd, (char *)response, sizeof(response), 0);

	close(recptfd);
	close(sockfd);
}