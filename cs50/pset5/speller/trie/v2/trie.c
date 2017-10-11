// trie.c v2

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

trieNode* MEMPOOL = NULL;
trieNode* MEMPOOLINDEX = NULL;

// global var to keep track of the size of the trie
int SIZE = 0;

// allocate memory for the specified number of nodes
void trieCreate() {
    if (MEMPOOL == NULL) {
        MEMPOOL = calloc(NUM_NODES, sizeof(trieNode));
        MEMPOOLINDEX = MEMPOOL;
    }
    
}

int trieInsert(const char* word) {
    
    trieNode* root = MEMPOOL;
    
	const char* c = NULL;
	for (c = word; *c != '\n' || *c == '\0'; c++) {

	    int offset = trieCharIndex(*c);

        // check if node for this char exists
    	if (root->children[offset] == NULL) {
    	    
    	    // check if we've used all our memory 
    	    //if (MEMPOOLINDEX - MEMPOOL < NUM_NODES)
    	   
    	    // point node to next mempool slot 
    		root->children[offset] = MEMPOOLINDEX;
    		MEMPOOLINDEX += 1;

        }
        
        // move root to the next node
        root = root->children[offset];
	}

    // assert, we're at the end of a word	
    if (*c == '\n' || *c == '\0') {
        root->is_word = true;
	    SIZE++;
    }
    return 0;
}


// Searches trie for word, returns True if word is found
bool trieSearch(const char* word) {
 
    trieNode* root = (trieNode*)MEMPOOL;
 
    // loop over characters in word
    const char * c = NULL;
	for (c = word; *c != '\0' && *c != '\n'; c++) {
	
	    int i = trieCharIndex(*c);
    
	    // if node at this index is NULL return false
	    if (root->children[i] == NULL)
	        return false;
	        
        // move to next node	    
	    root = root->children[i];

	}
	
	//if at end of word, return true
	if ((*c=='\0' || *c != '\n') && root->is_word)
	    return true;
	    
    return false;
}

// Counts the number of words in the Trie
int trieSize() {

    return SIZE;

}

// Frees the Trie from memory
int trieDestroy() {
    
    free(MEMPOOL);
    return 0;
    
}

// Calculate index of the character 
int trieCharIndex(char c) {
    
    if (c == '\'') return 26;
    
    else return tolower(c) - 'a';

}

int printTrie() {
    return printTrieNode(MEMPOOL);
}

int printTrieNode(trieNode* node) {
    
    trieNode* firstChild = NULL;
    
    for(int i=0; i<MAX_CHILD_NODES; i++) {
        
        if (node->children[i] != NULL){
            
            if (firstChild == NULL)
                firstChild = node->children[i];
            
          printf("[");
          if (i == 26) printf("%c", 39);
          else printf("%c", i+97);
          
          if (node->children[i]->is_word) printf("w");
          printf("]");  
            
        } else
            printf("[]");
    }

    printf("\n");
    
    if (firstChild != NULL) printTrieNode(firstChild);

    return 0;

}