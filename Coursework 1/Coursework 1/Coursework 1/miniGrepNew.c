/*  Davide Maurilio Morello - Matric Number 40219838 - Computing Science
	More information regarding the complexity or other choices can be found
	in the report.
*/

#define _CRT_SECURE_NO_WARNINGS // VS2015 setting to use fopen instead of fopen_s
#define MAX_LEN 255 // size of the reading buffer

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "commandDataInit.h"
#include "stringFuncs.h"


/*
	writes to output file or stdout
*/

void outputData(commandData *grepData, unsigned int lineNumber, unsigned int occurrence, char mainString[])
{
	fprintf(grepData->outputFile, "\nWord ''%s'' found: \n",grepData->word);
	fprintf(grepData->outputFile, "Occurrence %d found on line %d\n", occurrence, lineNumber);
	fprintf(grepData->outputFile, "String found inside word ''%s'' \n\n", mainString);
}

/*
	Prints help information
*/

void printHelp()
{
	printf("\nGeneral structure: miniGrep string -i input -o output\n\n");
	printf("INPUT CONTROL\n\n");
	printf("-i fileName        if not set, stdin (console input) will be used\n\n");
	printf("OUTPUT CONTROL\n\n");
	printf("-o fileName        if not set, stdout (console output) will be used\n\n");
	printf("OTHER SETTINGS\n\n");
	printf("-c the research is NON case sensitive\n");
	printf("-e endless mode, the command will ask for infinite input if STDIN is set as input source\n");
	printf("--h displays command information\n");
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
	initCommand(grepData, argc, argv);  // sets the options based on the arguments

	if (grepData->help == 1)
	{
		printHelp();
		return 0;
		
	}

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

	return 0;
}