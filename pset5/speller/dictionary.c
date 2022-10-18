// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
int hash_para = 4;
const unsigned int N = 456976;

// Hash table
node *table[N];
//unsigned int hash_no;
int size_count;



// Hashes word to a number
unsigned int hash(const char *word)             // Hash function obtained from http://www.cse.yorku.ca/~oz/hash.html //
{
    unsigned int hash_no = 5381;
    int c;
    while ((c = tolower(*word++)))
    {
        hash_no = ((hash_no << 5) + hash_no) + c; /* hash * 33 + c */
    }    
    return hash_no % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word_load[LENGTH +1];               // Initialize array 'word' to read words into
    FILE *f = fopen(dictionary, "r");   // Open dictionary file to read

    if (f == NULL)                      // Check that file can be opened
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    
    size_count = 0;                         // Initialize dictionary word count to zero
    
    while (fscanf(f, "%s", word_load) != EOF)    // Reads one string from dictionary until EOF is reached
    {
        node *n = malloc(sizeof(node));     // Allocate memory for node
        if (n == NULL)
        {
            return false;
        }
        
        strcpy(n->word, word_load);              // Copy string from file to allocated node
        n->next = NULL;                     // Set next pointer of node to NULL.
        
       
        int hash_no = hash(word_load);                         // Run has function
         
        
        if (table[hash_no] == NULL)         // If no words already in this hash number position, set pointer to n
        {
            table[hash_no] = n;
        }
        
        else 
        {
            node *tmp = table[hash_no];     // Initiate temp pointer
            
            while (tmp->next != NULL)       // Follow string of pointers at existing hash number position
            {
                tmp = tmp->next;
            }
            tmp->next = n;                  // Set pointer of last linked list item to n
            
        }
        size_count++;                       // Increment dictionary word count
    }
    fclose(f);
    return true;
}



// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    
    return size_count;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hash_no = hash(word);
    
    if (table[hash_no] == NULL)         // If no words already in this hash number position, set pointer to n
    {
        return false;
    }
    
    else
    {
        node *tmp = table[hash_no];
        
        while (tmp != NULL)
        {
            if (!strcasecmp(word,tmp->word))
            {
                return true;
            }
            tmp = tmp->next;
            
        }
        return false;
    }
    
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
   for (int i = 0; i < N; i++)
   {
        node *cursor = table[i];
        node *temp = cursor;
        
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}


/*  OLD HASH FUNCTION

hash_no = 0;
//    int buckets = hash_para; 
    
    for (int i = 0; i < buckets; i++)
    {
        int ascii = tolower(*(word + i));            // Convert character to ascii
        
        if (ascii > 96 && ascii < 123)
        {
            hash_no += (ascii - 97)*(pow(16, (float)buckets - (i + 1)));
        }
        
        else if (ascii == 39)
        {
            buckets ++;
        }
        
        else
        {
            return 0;
        }
        
    } */
    