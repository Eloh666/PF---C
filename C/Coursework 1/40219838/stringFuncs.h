/*
	Functions meant to work on every string, not necessarely related to the commandData data structure.
*/


#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
		return endIndex + 1;                      // found, and substring ends at endIndex
}