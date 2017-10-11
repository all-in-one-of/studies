// trie.c v1

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "trie.h"

trieNode* TRIE_ROOT = NULL;

// Builds a new Trie, returns a pointer to the Trie
void trieCreate() {
    
    if (TRIE_ROOT == NULL)
        TRIE_ROOT = malloc(sizeof(trieNode));

    for (int i=0; i<MAX_CHILD_NODES; i++) 
        TRIE_ROOT->children[i] = NULL;

    TRIE_ROOT->is_word = false;
    
}

// Inserts a word into the Trie
int trieInsert(const char* word) {
    
    trieNode* root = TRIE_ROOT;
    
    // loop over chars in word
	const char* c = NULL;
	for (c = word; *c != '\0' && *c != '\n'; c++) {
	  
	    // get index from ascii value
	    int offset = trieCharIndex(*c);
	  
	    // if node at this index is NULL, malloc new node
	    if (root->children[offset] == NULL) 
	        root->children[offset] = malloc(sizeof(trieNode));

            // init values    
            for (int j=0; j<MAX_CHILD_NODES; j++) 
                root->children[offset]->children[j] = NULL;
            root->children[offset]->is_word = false;
	    
        // move to next node
	    root = root->children[offset];   

	}
	
	//if at end of word, set is_word to true
	if (*c=='\0' || *c == '\n')
	    root->is_word = true;
	
    return 0;
}

// Searches trie for word, returns True if word is found
bool trieSearch(const char* word) {
 
    trieNode* root = TRIE_ROOT;
 
    // loop over characters in word
    const char * c = NULL;
	for (c = word; *c != '\0' && *c != '\n'; c++) {
	
	    int offset = trieCharIndex(*c);
    
	    // if node at this index is NULL return false
	    if (root->children[offset] == NULL)
	        return false;
	        
        // move to next node	    
	    root = root->children[offset];

	}
	
	//if at end of word, return true
	if ((*c=='\0' || *c != '\n') && root->is_word)
	    return true;
	    
    return false;
}

// Counts the number of words in the Trie
int trieSize() {
    
    return trieNodeSize(TRIE_ROOT);

}

int trieNodeSize(trieNode* node) {

    int count = 0;
    
    for (int i=0; i<MAX_CHILD_NODES; i++)
        if (node->children[i] != NULL) count += trieNodeSize(node->children[i]);
    
    if (node->is_word) count++;
    
    return count;
    
}

int trieDestroy() {
    
    return trieDestroyNode(TRIE_ROOT);
    
}

// Frees the Trie from memory
int trieDestroyNode(trieNode* root) {
    
    for (int i=0; i<MAX_CHILD_NODES; i++)
        if(root->children[i] != NULL) trieDestroyNode(root->children[i]);

    free(root);
    
    return 0;
    
}

// Calculate the index of the character 
int trieCharIndex(char c) {
    
    if (c == '\'') return 26;
    
    else return tolower(c) - 'a';

}

int printTrie() {
    return printTrieNode(TRIE_ROOT);
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