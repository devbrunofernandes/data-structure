#ifndef DATASTRUCTURES_RADIX_TREE_H
#define DATASTRUCTURES_RADIX_TREE_H

#include <stdbool.h>

typedef struct RadixTreeNode RadixTreeNode;

typedef struct RadixTree RadixTree;

RadixTree* radixCreate();

void radixInsert(RadixTree* tree, const char* key);

void radixDelete(RadixTree* tree, const char* key);

bool radixSearch(RadixTree* tree, const char* key);

void radixDestroy(RadixTree* tree);

#endif //DATASTRUCTURES_RADIX_TREE_H