#ifndef DATASTRUCTURES_BTREE_H
#define DATASTRUCTURES_BTREE_H

typedef struct BTreeNode BTreeNode;

typedef struct BTree BTree;

BTree* btreeCreate();

void btreeDestroy(BTree* tree);

void btreeInOrder(BTree* tree);

const int* btreeSearch(BTree* tree, int key);

void btreeInsert(BTree* tree, int key);

void btreeDelete(BTree* tree, int key);

#endif //DATASTRUCTURES_BTREE_H