/*
	Data Structure that holds the mini-grep information and related initialization functions.
*/

#define MIN(a,b) (((a)<(b))?(a):(b)) // min function
#define MIN_ARGS 2 // the min amount of args for the command to work
#define MAX_ARGS 8 // max number of args that will be read
// the number is 8, as -e will be ignored if stdin is the input

#pragma once

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
	int help; // -c 0 = no, 1 = yes
	int endless; // if set, it will require infinite lines from stdin
	char word[MAX_LEN]; // the word to look for
	char inputFileName[MAX_LEN]; // given input file name
	char outputFileName[MAX_LEN]; // given output file name
	FILE* inputFile; // input file OR stdin
	FILE* outputFile; // output file OR stdout
} commandData;

/*
sets the default options
*/

void comDataDefaultInit(commandData * grepData, char word[])
{
	grepData->mode = 0;
	grepData->notCaseSensitive = 0;
	grepData->endless = 0;
	grepData->inputFile = stdin;
	grepData->outputFile = stdout;
	strcpy(grepData->word, word);
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


void initCommand(commandData *grepData, int argc, char *argv[]) /*
															Initiliaze minigrep structure based on
															the given arguments. The position does not matter.
															*/
{
	if (!strcmp(argv[1], "--h"))
	{
		grepData->help = 1;
		return;
	}
	comDataDefaultInit(grepData, argv[1]); // sets default values for the various command parameters
	int flagI = 0;
	int flagO = 0;
	int ceil = MIN(argc, MAX_ARGS);
	for (int i = MIN_ARGS; i < ceil; i++)
	{
		if (!strcmp("-i", argv[i]) && !flagI)            // check for input given
		{
			flagI = 1;
			(grepData->mode)++;
			if (i + 1 < ceil)
			{
				strcpy(grepData->inputFileName, argv[i + 1]);
			}
		}
		if (!strcmp("-o", argv[i]) && !flagO)           // check for output given
		{
			flagO = 1;
			grepData->mode = (grepData->mode) + 2;
			if (i + 1 < ceil)
			{
				strcpy(grepData->outputFileName, argv[i + 1]);
			}
		}
		if (!strcmp("-c", argv[i]))          // check for -c given
		{
			grepData->notCaseSensitive = 1;
		}
		if (!strcmp("-e", argv[i]))          // check for -e given
		{
			grepData->endless = 1;
		}
		if (!strcmp("--h", argv[i]))          // check for -h given
		{
			grepData->help = 1;
			return;
		}
		getFiles(&grepData);  // opens the files
	}
}