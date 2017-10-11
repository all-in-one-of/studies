/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false.
bool check(const char *word) {
    return trieSearch(word);
}

// Loads dictionary into memory. Returns true if successful else false.
bool load(const char *dictionary) {
    
    trieCreate();
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL) {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH+2];

    while (fgets(word, sizeof(word), fp)) {
        if (trieInsert(word) == 1) break;
    }

    fclose(fp);
    
    printTrie();
    
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded.
unsigned int size(void) {
    
    return trieSize();
}

// Unloads dictionary from memory. Returns true if successful else false.
bool unload(void) {
    
    if (trieDestroy() == 0) return true;
    else return false;
}
