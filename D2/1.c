#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	if(argc < 3){
		printf("Syntax: a.exe num1 num2");
		return;
	}
	printf("Sum: %d", atoi(argv[1]) + atoi(argv[2]));
}