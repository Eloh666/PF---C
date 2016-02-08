/*  Davide Maurilio Morello - Matric Number 40219838 - Computing Science
	More information regarding the complexity or other choices can be found
	in the report.
*/

#define _CRT_SECURE_NO_WARNINGS // VS2015 setting to use fopen instead of fopen_s
#define MIN_ARGS 2 // the min amount of args for the command to work
#define MAX_ARGS 8 // max number of args that will be read
#define MAX_LEN 255 // size of the reading buffer
#define MIN(a,b) (((a)<(b))?(a):(b)) // min function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct minigrep   // the struct that holds the data of the given command
{
	int mode; /* chosen modality of the function
								0 == no io files selected
								1 == only input
								2 == only output
								3 == both selected */

	int notCaseSensitive; // -c 0 = no, 1 = yes
	int endless; // if set, it will require infinite lines from stdin
	char word[MAX_LEN]; // the word to look for
	char inputFileName[MAX_LEN]; // given input file name
	char outputFileName[MAX_LEN]; // given output file name
	FILE* inputFile; // input file OR stdin
	FILE* outputFile; // output file OR stdout
} commandData;


// prints the occurences to output file or stdout
void outputData(commandData *grepData, unsigned int lineNumber, unsigned int occurrence, char mainString[])
{
	fprintf(grepData->outputFile, "\nWord ''%s'' found: \n",grepData->word);
	fprintf(grepData->outputFile, "Occurrence %d found on line %d\n", occurrence, lineNumber);
	fprintf(grepData->outputFile, "String found inside word ''%s'' \n\n", mainString);
}



void setMode(commandData *grepData, int argc, char *argv[]) /* 
																Initiliaze minigrep structure based on 
															    the given arguments. The position does not matter.
															*/
{
	int flagI = 0;
	int flagO = 0;
	int ceil = MIN(argc, MAX_ARGS);
	for (int i = MIN_ARGS; i < ceil; i++)
	{
		if (strcmp("-i", argv[i]) == 0 && !flagI)            // check for input given
		{
			flagI = 1;
			(grepData->mode)++;
			if (i + 1 < ceil)
			{
				strcpy(grepData->inputFileName, argv[i + 1]);
			}
		}
		if (strcmp("-o", argv[i]) == 0 && !flagO)           // check for output given
		{
			flagO = 1;
			grepData->mode = (grepData->mode) + 2;
			if (i + 1 < ceil)
			{
				strcpy(grepData->outputFileName, argv[i + 1]);
			}
		}
		if (strcmp("-c", argv[i]) == 0 && !flagO)          // check for -c given
			grepData->notCaseSensitive = 1;
		if (strcmp("-e", argv[i]) == 0 && !flagO)          // check for -c given
			grepData->endless = 1;
	}
}


/* 
	Simple subString checker with case sensitive check option, more in the report.
	If b is not subString of a, returns -1, else returns the index of the mainString after the end of the subString.
*/
int isSubString(char * mainString, char * subString, int index, int notCaseSensitive)
{
	size_t mainLen = strlen(mainString);                   // size of the mainString
	size_t subLen = strlen(subString);                     // size of the subString

	if (subLen > mainLen)
		return -1;

	int notFound = 1;
	int endIndex = 0;
	for (int i = index, j = 0; i < mainLen && notFound && (mainLen - i) >= (subLen - j); i++)
	{   
		if (((notCaseSensitive && tolower(mainString[i]) == tolower(subString[j])) // -c check
			|| mainString[i] == subString[j]) // standard case sensitive check
			&& (mainLen - i) >= (subLen - j)) /* check if there will be enough room to hold
											     substring at this stage of the main string */
		{
			j++;
			if (j >= subLen)                  // break if the substring has been indeed found
			{
				notFound = 0;
				endIndex = i;
			}
		}
		else
			j = 0;
	}
	if (notFound)                             // no sub string found
		return -1;
	else
		return endIndex+1;                      // found, and substring ends at endIndex
}

/*
	The functioncalled by the caller "findOccurrences" recursively checks a string from a given index for the occurrence of a
	given substring, if it finds one, prints the occurrence.
*/
void findOccurrencesPrime(commandData *grepData, char mainString[], unsigned int lineNumber, unsigned int *occurrence, int index)
{
	int newIndex = isSubString(mainString, grepData->word, index, grepData->notCaseSensitive);
	if (newIndex != -1) //if word has been found inside the substring
	{
		(*occurrence)++;
		outputData(grepData, lineNumber, *occurrence, mainString);
		findOccurrencesPrime(grepData, mainString, lineNumber, occurrence, newIndex);
	}
}

/*
simple caller for the recursive function to start from 0
*/
void findOccurrences(commandData *grepData, char mainString[], unsigned int lineNumber, unsigned int *occurrence)
{
	findOccurrencesPrime(grepData, mainString, lineNumber, occurrence, 0); // more on the CW report
}

/*
	opens the input/output files depending on the -i or -o options
*/
void getFiles(commandData **grepData)
{
	switch ((*grepData)->mode)
	{
	case 3:
	case 2:
		(*grepData)->outputFile = fopen((*grepData)->outputFileName, "w");
		if ((*grepData)->mode == 2)
			break;
	case 1:
		(*grepData)->inputFile = fopen((*grepData)->inputFileName, "r");
		break;
	}
}

/*
	Main loop for the command. Reads the file chunking it into substrings, generally single words.
	Once a chunk has been gathered calls checks wether it contains the string to look for, if it so
	the string is output according to the chosen output file.
*/

void grepLoop(commandData *grepData)
{
	int count;
	int bufferSize;
	unsigned int lineNumber = 1;
	unsigned int occurrence = 0;
	unsigned short newLineFound = 0;

	char *buffer;

	if (grepData->inputFile == stdin)
		printf("\nInsert lines of text, CTRL-C to stop at any time: ");
	
	while (!feof(grepData->inputFile))  // goes until the end of the file
	{
		if(newLineFound)
		{
			if (grepData->inputFile == stdin && !grepData->endless)
				break;
			lineNumber++;
			newLineFound = 0;
		}
		bufferSize = MAX_LEN;
		buffer = malloc(bufferSize + 1 * sizeof(char)); /* allocates the buffer to the starting
														   buffer size of MAX_LEN + 1 extra space for \0 */
		count = 0;
		if (buffer == NULL)
		{
			printf("Allocation failed.\n");     /* returns if any allocation fails */
			return;
		}
		while (EOF != (buffer[count] = fgetc(grepData->inputFile)) && buffer[count] != ' ')  /*
																							 reads character 
																							 until a space or EOF																						 
																							 */
		{
			if (buffer[count] == '\n')
			{
				newLineFound = 1; // updates the number of current line for the next call if a \n char has been found
				break;  // breaks if a new line char has been found (more on the CW)
			}
			count++;
			if (count > bufferSize)
			{
				bufferSize *= 2;
				buffer = realloc(buffer, (bufferSize + 1) * sizeof(char));  // doubles the buffer if the file is not over
			}
			if (buffer == NULL)
			{
				printf("Allocation failed\n"); /* returns if any allocation fails */
				return;
			}
		}
		buffer[count] = '\0'; // ends the string with a \0 character
		findOccurrences(grepData, buffer, lineNumber, &occurrence); // calls the string checker function
		free(buffer);
	}
}

int main(int argc, char *argv[])
{
	/*
		To work the commands needs at least 1 word to look for as first argument, if not given, returns an error.
	*/
	if (argc < MIN_ARGS)
	{
		printf("\nError: the command requires at least 1 argument.\n");
		return -1;
	}

	commandData *grepData = malloc(sizeof(commandData)); // initialise the structure to hold the command data

	// sets the default options
	grepData->mode = 0;
	grepData->notCaseSensitive = 0;
	grepData->endless = 0;
	grepData->inputFile = stdin;
	grepData->outputFile = stdout;
	strcpy(grepData->word, argv[1]);

	setMode(grepData, argc, argv);  // sets the options based on the arguments

	getFiles(&grepData);  // opens the files

	if (grepData->outputFile == NULL || grepData->inputFile == NULL) // returns an error if there a problem opening any of the files
	{
		printf("\nError: File not found\n");
		return -1;
	}
	
	printf("\n");  // unecessary prints just to make everything look tidier
	grepLoop(grepData);
	printf("\n");



	if (grepData->inputFile != stdin)  // closes files if != default options
		fclose(grepData->inputFile);
	if (grepData->outputFile != stdout)
		fclose(grepData->outputFile);

	printf("\n\nDone\n\n"); // just to let the user know whether or not function is done

	return 0;
}