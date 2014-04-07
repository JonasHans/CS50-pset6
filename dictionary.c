/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 * Jonas van Oenen
 * 10670947
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
#define HASHTABLE_SIZE 3500
// number of words loaded into the dictionary
int wordCount = 0;

/**
 * Creates a linked list.
 */
typedef struct linkedList
{
	char* word;
	struct linkedList *nextList;
}
// create an intitial linked list
linkedList;
// create a hash table of linked lists
linkedList* hashTable[HASHTABLE_SIZE];

/**
 * Returns the hash value of the word
 */
int hash(const char* word)
{
    int wordLen = strlen(word);
    int hashSum = 0;
    
    // calculates the sum of the numeric values of the characters in a 
    // specified word
    for(int i = 0; i < wordLen; i++)
    {
    	hashSum += word[i];
    }
    return hashSum%HASHTABLE_SIZE;
}
	
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char uncheckedWord[LENGTH+1];
    linkedList* tempList = NULL;
    
    // convert all uppercase letters to lowercase
    for(int i = 0; i < strlen(word); i++)
    {
    	int lowerLetter = tolower(word[i]);
    	uncheckedWord[i] = (char)lowerLetter;
    }
    // terminate this word
    uncheckedWord[strlen(word)] = '\0';
    
    // the temporary list which is used for checking
    tempList = hashTable[hash(uncheckedWord)];
    // if the temporary list is empty the word must be mispelled and it returns false
    if(!tempList)
    {
    	return false;
    }
    
    // if not null go through all the linked lists and if it matches word is correct and
    // it returns true
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
 * Loads dictionary into memory.  Returns true if successful else false
 */
bool load(const char* dictionary)
{
   FILE* fp = NULL;
   int hashValue = 0 ;
   char dictWord[LENGTH+1];
   
   // open the dictionary
   fp = fopen(dictionary, "r");
   
   // if dictionary is empty return false
   if(fp == NULL)
   {
   	return false;
   }
   
   // read the dictionary and create the hash table
   while(fscanf(fp,"%s\n", dictWord) != EOF)
   {
	   	// create new linkedList size of linkedlist
	   	linkedList* newList = malloc(sizeof(linkedList));
	   	// allocate the maximum size of the word for memory
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
	linkedList* tempList = NULL;
	linkedList* tempList2 = NULL;
	
	// goes through all of the hashtable
	for(int i = 0; i < HASHTABLE_SIZE;i++)
	{
		tempList = hashTable[i];
		// if there is only one linked list present free this linked list
		if(tempList && !tempList->nextList)
		{
			free(tempList->word);
			free(tempList);
		}else
		{
			// goes through all the linked list and frees them one at a time
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
