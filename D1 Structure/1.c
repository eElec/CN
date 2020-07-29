#include <stdio.h>

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void main(){
	int a, b;

	printf("Enter two numbers: ");
	scanf("%d", &a);
	scanf("%d", &b);

	printf("a: %d\n", a);
	printf("b: %d\n", b);

	swap(&a, &b);

	printf("\nAfter swap\n");
	printf("a: %d\n", a);
	printf("b: %d\n", b);
}