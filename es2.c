#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void main()
{
	float acc = 0;
	int total = 0;
	int input = 0;
	while(input != -1)
	{
		printf("Please enter a number: ");
		scanf("%d", &input);
		if(input != -1)
		{
			acc+= input;
			total++;
		}
	}
	printf(" acc : %f  --- tot : %d ", acc, total);
	if(total == 0)
		printf("No marks entered");
	else
		printf("Your average is %f ", acc/total);
}
