// Coursework 1.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#define MIN_ARGS 2
#define MAX_ARGS 8
#define MAX_LEN 200
#define MIN(a,b) (((a)<(b))?(a):(b))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setMode(unsigned short *status, char inputName[], char outputName[], unsigned short *caseSensitive, int argc, char *argv[]) // sets the status && the input/output
{
	int flagI = 0;
	int flagO = 0;
	int ceil = MIN(argc, MAX_ARGS);
	for (int i = MIN_ARGS; i < ceil; i++)
	{
		if (strcmp("-i", argv[i]) == 0 && !flagI)
		{
			flagI = 1;
			*status = (*status) + 1;
			if (i + 1 < ceil)
			{
				strcpy(inputName, argv[i + 1]);
			}
		}
		if (strcmp("-o", argv[i]) == 0 && !flagO)
		{
			flagO = 1;
			*status = (*status) + 2;
			if (i + 1 < ceil)
			{
				strcpy(outputName, argv[i + 1]);
			}
		}
		if (strcmp("-c", argv[i]) == 0 && !flagO)
			*caseSensitive = 1;
	}
}

int isSubString(char * mainString, char * subString, int index)
{
	int mainLen = strlen(mainString);
	int subLen = strlen(subString);
	int notFound = 1;
	int endIndex = -1;
	for (int i = index, j = 0; i < mainLen && notFound && (mainLen - i) >= (subLen - j); i++)
	{
		if (mainString[i] == subString[j] && (mainLen - i) >= (subLen - j))
			j++;
		else if (j >= subLen)
		{
			notFound = 0;
			endIndex = i;
		}
		else
			j = 0;
	}
	if (notFound)
		return 0;
	else
		return endIndex;
}

void findOccurrencesPrime(char word[], char mainString[], unsigned int lineNumber, unsigned int *occurrence, int index)
{
	int newIndex = isSubString(mainString, word, index);
	if (newIndex)
	{
		(*occurrence)++;
		printf("\n -------> FOUND! : %s\n", mainString);
		findOccurrencesPrime(word, mainString, lineNumber, occurrence, newIndex);
	}
}

void findOccurrences(char word[], char mainString[], unsigned int lineNumber, unsigned int *occurrence)
{
	findOccurrencesPrime(word, mainString, lineNumber, occurrence, 0);
}



void getFiles(unsigned short mode, char inputName[], char outputName[], FILE** input, FILE** output)
{
	switch (mode)
	{
	case 3:
	case 2:
		*output = fopen(outputName, "w");
		if (mode == 2)
			break;
	case 1:
		*input = fopen(inputName, "r");
	}
	if (output == NULL || input == NULL)
	{
		printf("\nError: File not found\n");
		return;
	}
}

void grepLoop(char keyWord[], char inputName[], char outputName[], unsigned short mode, unsigned short caseSensitive, FILE* input, FILE* output)
{
	int len;
	unsigned int lineNumber = 1;
	unsigned int occurrence = 0;
	char *buffer;
	unsigned short newLineFound = 0;

	while (!feof(input))
	{
		if(newLineFound)
		{
			lineNumber++;
			newLineFound = 0;
		}
		buffer = malloc(MAX_LEN + 1 * sizeof(char));
		len = 0;
		if (buffer == NULL)
		{
			printf("Allocation failed.\n");
			return;
		}
		while (EOF != (buffer[len] = fgetc(input)) && buffer[len] != ' ')
		{
			if (buffer[len] == '\n')
			{
				newLineFound = 1;
				break;
			}
			len++;
			if (len > MAX_LEN)
				buffer = realloc(buffer, (len + 1) * sizeof(char));
			if (buffer == NULL)
			{
				printf("Allocation failed\n");
				return;
			}
		}
		buffer[len] = '\0';
		findOccurrences(keyWord, buffer, lineNumber, &occurrence);
		free(buffer);
	}
}


int main(int argc, char *argv[])
{
	unsigned short modeSettings = 0; // chosen modality of the function
									 // 0 == no io files selected
									 // 1 == only input
									 // 2 == only output
									 // 3 == both selected
	unsigned short caseSensitive = 0;

	char inputName[MAX_LEN]; //input file if any
	char outputName[MAX_LEN]; //output file if any
	char keyWord[MAX_LEN];  // the string to look for
	FILE * input = stdin;
	FILE * output = stdout;
	
	if (argc < MIN_ARGS)
	{
		printf("\nError: the command requires at least 1 argument.\n");
		return -1;
	}

	strcpy(keyWord, argv[1]);
	setMode(&modeSettings, inputName, outputName, &caseSensitive, argc, argv);
	getFiles(modeSettings, inputName, outputName, &input, &output);
	grepLoop(keyWord, inputName, outputName, modeSettings, caseSensitive, input, output);

	if (input != stdin)
		fclose(input);
	if (output != stdout)
		fclose(output);

	return 0;
}