// Coursework 1.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS
#define MIN_ARGS 2
#define MAX_ARGS 8
#define MAX_LEN 255
#define MIN(a,b) (((a)<(b))?(a):(b))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod
{
	char data[MAX_LEN];
	char fullLine[MAX_LEN];
	char fullWord[MAX_LEN];
	int line;
	struct nod *next;
} node;

node *newnode(void)
{
	return (node *)malloc(sizeof(node));
}


void setMode(unsigned short *status, char inputName[], char outputName[],int argc, char *argv[]) // sets the status && the input/output
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
				strcpy(inputName, argv[i+1]);
			};
		};
		if (strcmp("-o", argv[i]) == 0 && !flagO)
		{
			flagO = 1;
			*status = (*status) + 2;
			if (i + 1 < ceil)
			{
				strcpy(outputName, argv[i + 1]);
			};
		};
		printf("\n----->>  %s\n", argv[i]);
	}
}

void buildList(node **head, node **tail)
{
	node *p = NULL;
	p = newnode();
	strcpy(p->data, "TEMP1");  //TODO add data
	strcpy(p->fullLine, "TEMP2");
	strcpy(p->fullWord, "TEMP3");
	p->line = 0;
	p->next = NULL;
	if (*head == NULL)
		*head = p;
	else
		(*tail)->next = p;
	*tail = p;
}

node* consoleIn(char word[])
{
	node *head = NULL;
	node *tail = NULL;
	char line[MAX_LEN*10];
	printf("\n\n\nPlease start typing the text to Mini-Grep. Once you are done simply enter an empty string (single enter keystroke):\n\n");
	printf("--->");
	scanf("%s", line);
	while (strcmp(line,"-end-"))
	{
		buildList(&head, &tail);
		printf("--->");
		scanf("%s", line);
	}
	return head;
}

node* fileIn(char word[], char input[])
{
	node *head = NULL;
	node *tail = NULL;
	char line[MAX_LEN * 10];
	FILE *fp = fopen(input, "r");
	printf("Reading from file %s", input);
	if (fp != NULL)
	{
		while (fscanf(fp, "%s", line) != EOF)
		{
			printf("---->%s\n", line);
			buildList(&head, &tail);
		}
	}
	else
		printf("Error: Could not open file %s.\n", input);
	return head;
}

void printList( node *head)
{
	if (head != NULL)
	{
		printf("%s\n", head->data);
		printList(head->next);
	}
}


int main(int argc, char *argv[])
{
	unsigned short modeSettings = 0; // chosen modality of the function
					  // 0 == no io files selected
					  // 1 == only input
					  // 2 == only output
					  // 3 == both selected

	char inputName[MAX_LEN]; //input file if any
	char outputName[MAX_LEN]; //output file if any
	char keyWord[MAX_LEN];  // the string to look for
	node * occurrences = NULL;
	
	if (argc < MIN_ARGS)
	{
		printf("Error: the command requires at least 1 argument.");
		return -1;
	};

	strcpy(keyWord, argv[1]);
	setMode(&modeSettings, inputName, outputName, argc, argv);
	if (modeSettings == 0 || modeSettings == 2)
	{
		occurrences = consoleIn(keyWord);
	}
	else
	{
		occurrences = fileIn(keyWord, inputName);
	}
	


	// ------------------------- Tests

	printList(occurrences);

	// -------------------------

	return 0;
		
}

