// Coursework 1.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#define MIN_ARGS 2
#define MAX_ARGS 8
#define MAX_LEN 1024
#define MIN(a,b) (((a)<(b))?(a):(b))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
	char fullWord[MAX_LEN];
	unsigned long long line;
	unsigned long long occurrence;
	struct nod *next;
} node;

node *newnode(void)
{
	return (node *)malloc(sizeof(node));
}

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

void buildList(node** head, node** tail, unsigned long long lineNumber, unsigned long long occurrence, char word[], char fullWord[])
{
	node *p = NULL;
	p = newnode();
	strcpy(p->fullWord, fullWord);
	p->line = lineNumber;
	p->occurrence = occurrence;
	p->next = NULL;
	if (*head == NULL)
		*head = p;
	else
		(*tail)->next = p;
	*tail = p;
}

void printList(node *head)
{
	if (head != NULL)
	{
		printf("Found in: %s\n", head->fullWord);
		printf("On line: %llu\n", head->line);
		printf("%llu Occurrence\n\n", head->occurrence);
		printList(head->next);
	}
}


void killList(node** head)
{
	node* p = NULL;
	while(*head != NULL)
	{
		p = *head;
		*head = (*head)->next;
		free(p);
	}
}

char* backAndForth(char word[], char subString[], char mainString[])
{
	long long mainStringLen = strlen(mainString);
	long long subStringLen = strlen(subString);
	long long index = mainStringLen - subStringLen;
	long long startIndex = 0;
	long long endIndex = 0;
	long long size = 0;
	for (long long i = index; i >= 0 && mainString[i] != ' '; i--)
		startIndex = i;
	for (long long i = index; i <= mainStringLen && mainString[i] != ' '; i++)
		endIndex = i;
	char* output = NULL;
	for (long long j = 0, i = startIndex; i <= endIndex && mainString[i] != '\n'; i++, j++)
	{
		size++;
		if(j == 0)
			output = malloc(size+1 * sizeof(char)); // +1 due to the \0 character necessary for each string
		else
			output = realloc(output, (size+1) * sizeof(char));
		if (output == NULL)
		{
			printf("Error: malloc function failed");
		}
		output[j] = mainString[i];
	}
	output[size] = '\0';
	return output;
	
}


void findOccurrences(char word[], char mainString[], char buffer[], node** head, node** tail, unsigned long long lineNumber, unsigned long long *occurrence)
{
	char other[MAX_LEN];  //TODO improve
	char *temp = strstr(mainString, word);
	if (temp != NULL)
	{
		(*occurrence)++;
		char *output = backAndForth(word, temp, buffer);
		buildList(head, tail, lineNumber, *occurrence, word, output);
		strcpy(other, &temp[strlen(word)]);
		free(output);
		findOccurrences(word, other, buffer, head, tail, lineNumber, occurrence);
	}
}


void grepLoop(char keyWord[], char inputName[], char outputName[], unsigned short mode, unsigned short caseSensitive)
{
	char line[MAX_LEN];  //TODO improve
	unsigned long long lineNumber = 0;
	unsigned long long occurrence = 0;
	node *head = NULL;
	node *tail = NULL;
	FILE * input = stdin;
	FILE * output = stdout;

	switch(mode)
	{
	case 3:
	case 2:
		output = fopen(outputName, "w");
		if (mode == 2)
			break;
	case 1:
		input = fopen(inputName, "r");
	}
	if (output == NULL || input == NULL)
	{
		printf("\nError: File not found\n");
		return;
	}
	while(fgets(line, MAX_LEN, input))
	{
		
		if (strstr(line, "\n") != NULL)
			lineNumber++;
		findOccurrences(keyWord, line, line, &head, &tail, lineNumber, &occurrence);
		printList(head);
		killList(&head);
	}
		

	//fclose(input);
	//fclose(output);
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
	

	if (argc < MIN_ARGS)
	{
		printf("\nError: the command requires at least 1 argument.\n");
		return -1;
	}

	strcpy(keyWord, argv[1]);
	setMode(&modeSettings, inputName, outputName, &caseSensitive, argc, argv);
	grepLoop(keyWord, inputName, outputName, modeSettings, caseSensitive);

	// ------------------------- Tests

	printf("\nDone\n");

	// -------------------------

	return 0;

}
