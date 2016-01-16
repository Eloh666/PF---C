#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

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

void drawSchema(int tree)
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
	int op = -1;
	
	while(op != 1 && op != 2)
	{
		printf("Do you want a triangle (1) or a Christmas Tree (2) ? Please pick your option: ");			
		scanf("%d", &op);
	}
	
	if(op == 1)
		drawSchema(0);
	else
		drawSchema(1);
	
	
}
