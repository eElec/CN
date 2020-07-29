#include <stdio.h>

struct pkt{
	unsigned char ch1;
	unsigned char ch2[2];
	unsigned char ch3;
};

void main(){
	unsigned int x;
	printf("Enter number: ");
	scanf("%d", &x);

	struct pkt C;
	C.ch1 = (x >> 0*8 & 0xFF);
	C.ch2[0] = (x >> 1*8 & 0xFF);
	C.ch2[1] = (x >> 2*8 & 0xFF);
	C.ch3 = (x >> 3*8 & 0xFF);

	printf("%x %x %x %x\n", C.ch1, C.ch2[0], C.ch2[1], C.ch3);

	int r = 0;
	r = r << 8 | C.ch3;
	r = r << 8 | C.ch2[1];
	r = r << 8 | C.ch2[0];
	r = r << 8 | C.ch1;
	printf("Original Number: %u\n", r);
}