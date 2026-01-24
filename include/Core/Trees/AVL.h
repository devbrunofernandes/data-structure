#ifndef DATASTRUCTURES_AVL_H
#define DATASTRUCTURES_AVL_H

typedef struct AVLNode AVLNode;

typedef struct AVL AVL;

AVL* avlCreate();

void avlInsert(AVL* tree, int key);

void avlDelete(AVL* tree, int key);

const int* avlSearch(AVL* tree, int key);

void avlInOrder(AVL* tree);

void avlDestroy(AVL* tree);

#endif //DATASTRUCTURES_AVL_H