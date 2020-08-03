#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
	int roll_no; 
	char name[50];
	float CGPA; 
};

void display(struct info *var){
	printf("Roll Number: %d", var->roll_no);
	printf("\nName: %s", var->name);
	printf("\nCGPA: %.2f", var->CGPA);
}

void main(int argc, char *argv[]){
	if(argc < 4){
		printf("Usage: ./a.out Roll Name CGPA");
		return;
	}
	
	struct info var;
	var.roll_no = atoi(argv[1]);
	strcpy(var.name, argv[2]);
	var.CGPA = atof(argv[3]);

	display(&var);
}