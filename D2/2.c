#include <stdio.h>
#include <stdlib.h>

void main(int argc, char *argv[]){
	if(argc < 6){
		printf("Enter 5 numbers\n");
		return;
	}
	
	int sum=0;
	for(int i=1; i<=5; i++){
		sum+=atoi(argv[i]);
	}

	float avg = sum / 5;
	printf("Avg: %.2f\n", avg);
}