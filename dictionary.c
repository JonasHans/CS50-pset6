/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// size of the hash table
int hashTableSize = 3500;
// number of words loaded into the dictionary
int wordCount = 0;

/**
 * Creates a linked list.
 */
typedef struct linkedList
{
	char *word;
	struct linkedList *nextList;
}
// create an intitial linked list.
linkedList;
// create a hash table of linked lists.
linkedList *hashTable[3500];

/**
 * Returns the hash value of the word.
 */
int hash(const char* word)
{
    int wordLen = strlen(word);
    return wordLen%3500;
}
	
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char uncheckedWord[LENGTH+1];
    linkedList *tempList;
    
    for(int i = 0; i < strlen(word); i++)
    {
    	int lowerLetter = tolower(word[i]);
    	uncheckedWord[i] = (char)lowerLetter;
    }
    uncheckedWord[strlen(word)] = '\0';
    
    tempList = hashTable[hash(word)];
    if(!tempList)
    {
    	return false;
    }
    
    while(tempList)
    {
    	if(!strcmp(tempList->word, uncheckedWord))
    	{
    		return true;
    	}
    	tempList = tempList->nextList;
    }
    return false;
    
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
   FILE *fp = NULL;
   int hashValue;
   char dictWord[LENGTH+1];
   
   // open the dictionary.
   if(!(fp = fopen(dictionary, "r")))
   {
   	return false;
   }
   
   for(int i = 0; i < 3500; i++)
   {
		hashTable[i] = NULL;
   }
   
   // read the dictionary and create the hash table.
   while(fscanf(fp,"%s\n", dictWord) != EOF)
   {
   	// create new linkedList size of linkedlis.
   	linkedList *newList = malloc(sizeof(linkedList));
   	// allocate the maximum size of the word for memory.
   	newList->word = malloc(strlen(dictWord)+1);
   	// copy the new word into the linked list 
   	strcpy(newList->word,dictWord);
  
   	hashValue = hash(dictWord);
   	
   	wordCount++;
   	
   	// sets the linkedlist in the hashtable to the new linkedlist, if there are other 
   	// linkedlists then the new list is made the head   	
   	if(hashTable[hashValue] == NULL)
   	{
   		hashTable[hashValue] = newList;
   	}else
   	{
   		newList->nextList = hashTable[hashValue];
   		hashTable[hashValue] = newList;
   	}   	
   	
   }
   	printf("Number of words loaded : %d\n", wordCount);
	return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
	linkedList *tempList;
	linkedList *tempList2;
	for(int i = 0; i < 3500;i++)
	{
		tempList = hashTable[i];
		if(tempList && !tempList->nextList)
		{
			free(tempList->word);
			free(tempList);
		}else
		{
			while(tempList)
			{
				tempList2 = tempList->nextList;
				free(tempList->word);
				free(tempList);
				tempList = tempList2;
			}
		}
		hashTable[i] = NULL;
	}
	return true;
}
