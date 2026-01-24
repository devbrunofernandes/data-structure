#ifndef DATASTRUCTURES_BPLUSTREE_H
#define DATASTRUCTURES_BPLUSTREE_H

typedef struct BPlusTreeNode BPlusTreeNode;

typedef struct BPlusTree BPlusTree;

typedef void (*BPlusCallback)(int key);

BPlusTree* bplusCreate();

void bplusDestroy(BPlusTree* tree);

void bplusDisplay(BPlusTree* tree);

const int* bplusSearch(BPlusTree* tree, int key);

void bplusIntervalSearch(BPlusTree* tree, int minor, int greater, BPlusCallback action);

void bplusInsert(BPlusTree* tree, int key);

void bplusDelete(BPlusTree* tree, int key);

#endif //DATASTRUCTURES_BPLUSTREE_H