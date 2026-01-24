#ifndef DATASTRUCTURES_BST_H
#define DATASTRUCTURES_BST_H

typedef struct BSTNode BSTNode;

typedef struct BST BST;

BST* bstCreate();

void bstInsert(BST* tree, int key);

void bstDelete(BST* tree, int key);

const int* bstSearch(BST* tree, int key);

void bstInOrder(BST* tree);

void bstDestroy(BST* tree);

#endif //DATASTRUCTURES_BST_H