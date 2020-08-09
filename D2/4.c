#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage: ./a.out IP Port\n");
		return;
	}
	printf("IP: %s\n", argv[1]);
	printf("Port: %d\n", atoi(argv[2]));
}