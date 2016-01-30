#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CHOICE
{
	ENTER = 0,
	PRINT = 1,
	EXIT = 2
};

struct student
{
	unsigned int matrix;
	char name[50];
	char address[100];
} Student;

struct student enterDetails(struct student stu)
{
	printf("\n\nPlease provide your matriculation number: ");
	scanf("%ud", &stu.matrix);
	printf("Please provide your matriculation full name: ");
	scanf("%s", &stu.name);
	printf("Please provide your matriculation address: ");
	scanf("%s", &stu.address);
	
	return stu;
}

void printDetails(struct student stu)
{
	if(stu.matrix != 0)
	{
		printf("\n\n");
		printf("Matriculation number: %ud\n", stu.matrix);
		printf("Name: %s\n", stu.name);
		printf("Address: %s\n", stu.address);
	}
	else
		printf("\nYou have not entered any detail yet, please choose the first option\n");
}

void main()
{
	int leave = 0;
	struct student stu;
	stu.matrix = 0;
	while(!leave)
	{
		char op[10];
		enum CHOICE choice;
		printf("\nWelcome to this incredibly useful tool: \n");
		printf("In order to enter a student detail, choose 0\n");
		printf("I norder to print the details, choose 1\n");	
		printf("If instead you wish to exit, please key in 2:   ");
		scanf("%s", &op);
		choice = atoi(op);
		
		switch(choice)
		{
			case ENTER:
				stu = enterDetails(stu);
				break;
			case PRINT:
				printDetails(stu);
				break;
			case EXIT:
				leave = 1;
				break;
			default:
				printf("Invalid input, try again.\n");
		}
	}
}
