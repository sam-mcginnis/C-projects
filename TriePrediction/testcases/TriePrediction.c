#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TriePrediction.h"

#define BUFFER 1024


// Helper function called by printTrie(). (Credit: Dr. S.)
void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0. (Credit: Dr. S.)
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];
	
	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

TrieNode *createNode()
{
	// credit Dr. S.
	int i;
	TrieNode *NewNode;
	
	NewNode= malloc(sizeof(TrieNode));
	if(NewNode == NULL)
	{
		free(NewNode);
		return NULL;
	}

	NewNode->count = 0;
	for (i = 0; i < 26; i++)
		NewNode->children[i] = NULL;
	
	NewNode->subtrie= NULL;

	return NewNode;
}

TrieNode *insert(TrieNode *root, char *character)
{
	// credit Dr. S.
	int i, index, length;
	TrieNode *temp;

	if (root == NULL)
		root = createNode();

	temp = root;

	length= strlen(character);
	for (i = 0; i < length; i++)
	{
		
		if(96 < character[i] && character[i]< 123 || 64 < character[i] && character[i]< 91)
		{

			
			index = tolower(character[i]) - 'a';

			if (temp->children[index] == NULL)
				temp->children[index] = createNode();
			

			temp = temp->children[index];	
		}
		
	}
	
	temp->count++;
	return root;
}
TrieNode *buildTrie(char *filename)
{
	// credit Dr. S.
	FILE *fp;
	TrieNode *root, *subtri;
	char buffer[BUFFER + 1];
	int i=0;

	root = NULL;
	subtri= NULL;
	fp = fopen(filename, "r");
	
	if(fp == NULL)
	{
		printf("File \"%s\" not found.\n Try again...\n", filename);
		return NULL;

	}
	
	while (fscanf(fp, "%s", buffer) != EOF)
		root = insert(root, buffer);

	fclose(fp);
	return root;
}

int processInputFile(TrieNode *root, char *filename)
{	
	FILE *fp;
	int num1, i=0;
	char buffer[BUFFER];
	fp=fopen(filename, "r");
	
	if(fp == NULL)
	{
		printf("File \"%s\" not found.\n Try again...\n", filename);
		return 0;

	}
	
	num1= fgetc(fp);
	while(num1!= EOF)
	{
		if( num1 == 33)
			printTrie(root, 0);

		num1=fgetc(fp);
	}	

	
	return 0;
}

TrieNode *destroyTrie(TrieNode *root)
{
	if(root == NULL)
		return NULL;

	free(root);
	
	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{ 
	int i;

	if (root == NULL)
		return NULL;


	return NULL;
}

void getMostFrequentWord(TrieNode *root, char *str)
{
}

int containsWord(TrieNode *root, char *str)
{
	return 0;
}

int prefixCount(TrieNode *root, char *str)
{
	return 0;
}

double difficultyRating(void)
{
	return 5.0;
}

double hoursSpent(void)
{
	return 12.0;
}

int main(int argc, char **argv)
{
	TrieNode *root;
	
	
	root = buildTrie(argv[1]);
	processInputFile(root, argv[2]);
	
	

	return 0;
}
