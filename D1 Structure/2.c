#include <stdio.h>
struct info{
	int roll_no;
	char name[50];
	float CGPA;
};

void outputS(struct info *ss){
	printf("\nRoll: %d", ss->roll_no);
	printf("\nName: %s", ss->name);
	printf("\nCGPA: %.2f", ss->CGPA);
}

void main(){
	struct info ss;
	printf("Enter the Roll: ");
	scanf("%d", &ss.roll_no);
	printf("Enter the Name: ");
	scanf("%s", &ss.name);
	printf("Enter the CGPA: ");
	scanf("%f", &ss.CGPA);
	outputS(&ss);
}