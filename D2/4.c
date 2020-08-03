#include <stdio.h>

void main(int argc, char *argv[]){
	if(argc < 3){
		printf("Usage: a.exe IP Port");
		return;
	}
	printf("IP: %s", argv[1]);
	printf("\nPort: %s", argv[2]);
}