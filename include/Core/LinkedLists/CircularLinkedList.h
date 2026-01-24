#ifndef DATASTRUCTURES_CIRCULAR_LINKEDLIST_H
#define DATASTRUCTURES_CIRCULAR_LINKEDLIST_H

#include <stdbool.h>

typedef struct CircularLinkedList CircularLinkedList;

CircularLinkedList* arrayToCircularLinkedList(int* A, int size);

CircularLinkedList* clCreate();

void clPrint(CircularLinkedList* cll);

void clDelete(CircularLinkedList *cll, int index);

void clInsert(CircularLinkedList* cll, int index, int x);

const int* clSearch(CircularLinkedList* cll, int x);

bool clContains(CircularLinkedList* cll, int x);

const int* clGet(CircularLinkedList* cll, int index);

#endif //DATASTRUCTURES_CIRCULAR_LINKEDLIST_H