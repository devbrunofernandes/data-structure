#ifndef DATASTRUCTURES_TRIE_H
#define DATASTRUCTURES_TRIE_H

#include <stdbool.h>

typedef struct TrieNode TrieNode;

typedef struct Trie Trie;

Trie* trieCreate();

void trieInsert(Trie* tree, const char* key);

void trieDelete(Trie* tree, const char* key);

bool trieSearch(Trie* tree, const char* key);

void trieDestroy(Trie* tree);

#endif //DATASTRUCTURES_TRIE_H