#ifndef TRIE_H
#define TRIE_H

enum { MAX_CHILD_NODES = 27 };

// Trie Structure
typedef struct trieNode {
	bool is_word;
	struct trieNode *children[MAX_CHILD_NODES];
} trieNode;


// Trie Algorithms
void trieCreate();
bool trieSearch(const char* word);
int trieInsert(const char* word);
int trieSize();
int trieNodeSize(trieNode * node);
int trieDestroy();
int trieDestroyNode(trieNode * node);

int trieCharIndex(char c);

int printTrie();
int printTrieNode(trieNode* node);

#endif