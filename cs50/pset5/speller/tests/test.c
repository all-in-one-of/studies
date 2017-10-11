#include <stdio.h>

#include "../dictionary.h"

int testTrie();

int main() {
    
    testTrie();
    return 0;

}

int testTrie() {

    printf("Creating Trie ... \n");
    trieCreate();

    printf("Inserting Word ... \n");
    trieInsert("pneumonoultramicroscopicsilicovolcanoconiosis");

    //printf("Inserting Word ... aardvark's \n");
    //trieInsert(t, "abcdefghijklmnopqrstuvwxyz'");

    printTrie();
    
    printf("Searching for Word it's ... \n");
    if (trieSearch("pneumonoultramicroscopicsilicovolcanoconiosis")) printf("success \n");

    printf("Searching for Word int ... \n");
    if (trieSearch("int")) printf("success \n");
    
    printf("The size of this Trie is %d \n", trieSize());
    
    printf("Destroying Trie ... \n");
    trieDestroy();

    return 0;
}
