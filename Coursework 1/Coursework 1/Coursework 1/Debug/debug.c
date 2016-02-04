#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

void main()
{
	int len;
	unsigned long long lineNumber = 0;
	unsigned long long occurrence = 0;
	char *buffer;
	FILE* input = fopen("text.txt","r");

	while (!feof(input))
	{
		buffer = malloc(1 + 1 * sizeof(char));
		len = 0;
		if (buffer == NULL)
		{
			printf("Allocation failed.\n");
			return;
		}
		while (EOF != (buffer[len] = fgetc(input)) && buffer[len] != '\n' && buffer[len] != ' ')
		{
			len++;
			buffer = realloc(buffer, (len + 2) * sizeof(char));
			if (buffer == NULL)
			{
				printf("Allocation failed\n");
				return;
			}
		}
		buffer[len] = '\0';
		printf("\n %llu ------> %s\n",lineNumber, buffer);

	}
}
