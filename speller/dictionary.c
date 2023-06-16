// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <cs50.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //create cursor node
    node *cursor = NULL;
    //Hash word
    int hash_value = hash(word);
    //Traverse linked list at table[hash_value] using string compare strcasmp()
    cursor = table[hash_value];
    while (cursor != NULL)
    if (strcasecmp(word, cursor->word) == 0)
    {
        return true;
    }
    else
    {
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char buffer[LENGTH+1];
    int hash_value;

    //1. Open dictionary file fopen()
    FILE *file = fopen(dictionary, "r");
    //2. fscanf(file, %s, word) to read strings one at a time
    while (fscanf(file, "%s", buffer) != EOF)
    {
        word_count++;
    //3.Create a new node for each word
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return NULL;
        }
        strcpy(new_word -> word, buffer); //copy word into node using strcpy
        new_word->next = NULL; //assign next field to node

    //4. Hash word to obtain hash value
        hash_value = hash(new_word -> word);

    //5. Insert node into hash table at that location
        if(table[hash_value] == NULL)
        {
            table[hash_value] = new_word; //point table at new_word
        }
        else
        {
            new_word->next = table[hash_value]; //point new_word at table[]
            table[hash_value] = new_word;
        }
    }

    if (fscanf(file, "%s", buffer) == EOF)
    {
        fclose(file);
        return true;
    }
    else
    {
        fclose(file);
        return false;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *ptr;
    for (int i=0; i<N; i++)
    {
        ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
            word_count--;
        }
    }
    if (word_count != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
