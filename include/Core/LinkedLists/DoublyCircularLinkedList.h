#ifndef DATASTRUCTURES_DOUBLY_CIRCULAR_LINKEDLIST_H
#define DATASTRUCTURES_DOUBLY_CIRCULAR_LINKEDLIST_H

#include <stdbool.h>

typedef struct DoublyCircularLinkedList DoublyCircularLinkedList;

DoublyCircularLinkedList* arrayToDoublyCircularLinkedList(int* A, int size);

DoublyCircularLinkedList* dclCreate();

void dclPrint(DoublyCircularLinkedList* dcl);

void dclDelete(DoublyCircularLinkedList* dcl, int index);

void dclInsert(DoublyCircularLinkedList* dcl, int index, int x);

const int* dclSearch(DoublyCircularLinkedList* dcl, int x);

bool dclContains(DoublyCircularLinkedList* dcl, int x);

const int* dclGet(DoublyCircularLinkedList* dcl, int index);

#endif //DATASTRUCTURES_DOUBLY_CIRCULAR_LINKEDLIST_H