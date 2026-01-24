#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

typedef struct DoublyLinkedNode {
    struct DoublyLinkedNode *prev;
    int data;
    struct DoublyLinkedNode *next;
} DoublyLinkedNode;

typedef struct DoublyLinkedList DoublyLinkedList;

DoublyLinkedList* dllCreate();

DoublyLinkedList* arrayToDoublyLinkedList(int* A, int size);

void dllDisplay(DoublyLinkedList* ll);

const int* dllFront(DoublyLinkedList* ll);

const int* dllBack(DoublyLinkedList* ll);

void dllInsert(DoublyLinkedList* ll, int index, int value);

void dllDelete(DoublyLinkedList* ll, int index);

void dllPopFront(DoublyLinkedList* ll);

void dllPushFront(DoublyLinkedList* ll, int value);

void dllPopBack(DoublyLinkedList* ll);

void dllPushBack(DoublyLinkedList* ll, int value);

void dllDestroy(DoublyLinkedList* ll);

void dllReverse(DoublyLinkedList* ll);

#endif