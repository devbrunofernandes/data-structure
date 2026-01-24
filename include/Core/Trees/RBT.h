#ifndef DATASTRUCTURES_RBT_H
#define DATASTRUCTURES_RBT_H

typedef struct RBTNode RBTNode;

typedef struct RBT RBT;

RBT* rbtCreate();

void rbtInsert(RBT* tree, int key);

void rbtDelete(RBT* tree, int key);

const int* rbtSearch(RBT* tree, int key);

void rbtInOrder(RBT* tree);

void rbtDestroy(RBT* tree);

#endif //DATASTRUCTURES_RBT_H