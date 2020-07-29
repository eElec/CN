#include <stdio.h>

void main(){
	int x;
	printf("Enter number: ");
	scanf("%d", &x);
	char *c = (char *)&x;

	for(int i=0; i<sizeof(int); i++){
		printf("%d\n", *(c + i));
	}

	for(int i=0; i<sizeof(int); i++){
		printf("%d\n", (char)(x >> (i*8) & 0x000000FF));
	}
}