#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum CHOICE
{
	STARNAME = 0,
	TRIANGLE = 1,
	XMTREE = 2,
	EXIT = -1
};

void printAst(int nameLen)
{
	int i;
	for(i = 0; i < nameLen; i++)
	{
		printf("*");
	}
	printf("\n");
}

void printName(){
	char myName[100];
	int i;
	printf("Inserisci il tuo nome: ");
	scanf("%s", &myName);
	int nameLen = strlen(myName);
	printAst(nameLen+6);
	printf("*  %s  *\n",myName);
	printAst(nameLen+6);
}

void drawStars(int len, int stars)
{
	int i;
	int blanks = len - stars;
	printf("   ");
	for(i = 1; i <= len; i++)
	{
		if(i <= blanks/2  || i > stars + blanks/2)
			printf(" ");
		else
			printf("*");
	}
	printf("\n");
				
}

void drawTree(int tree)
{
	int height = 0;
	int i;
	int stars = 1;
	int totLen = 1;
	printf("Please choose the height of your christmas tree: ");
	scanf("%d", &height);
	printf("\n");
	for(i = 1; i <= height; i++)
	{
		totLen += 2;
	}
	for(i = 1; i <= height; i++ )
		{
			if(i != 1)
				stars += 2;
			drawStars(totLen, stars);
		}
	if(height != 0 && tree)
		drawStars(totLen, 1);	
}

void main()
{
	int leave = 0;
	while(!leave)
	{
		char op[10];
		enum CHOICE choice;
		printf("\n\nWelcome to this incredibly useful tool: \n");
		printf("In order to print your starred name, choose 0\n");
		printf("I norder to print a triangle, choose 1\n");	
		printf("If instead you wish to print a Xmas Tree, please key in 2.\n");
		printf("Lastly, to exit please key in -1:    ");
		scanf("%s", &op);
		system("cls");
		choice = atoi(op);
		
		switch(choice)
		{
			case STARNAME:
				printName();
				break;
			case TRIANGLE:
				drawTree(0);
				break;
			case XMTREE:
				drawTree(1);
				break;
			case EXIT:
				leave = 1;
				break;
			default:
				printf("Invalid input, try again.\n");
		}
	}
}
