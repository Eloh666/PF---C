#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void printAst(int nameLen)
{
	int i;
	for(i = 0; i < nameLen; i++)
	{
		printf("*");
	}
	printf("\n");
}

void main(){
	char myName[100];
	int i;
	printf("Inserisci il tuo nome: ");
	scanf("%s", &myName);
	int nameLen = strlen(myName);
	printAst(nameLen+6);
	printf("*  %s  *\n",myName);
	printAst(nameLen+6);
}
