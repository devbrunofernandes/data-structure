#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

typedef struct LinkedListNode {
    int data;
    struct LinkedListNode *next;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* first;
    LinkedListNode* last;
    int length;
} LinkedList;

LinkedList* llCreate();

LinkedList* arrayToLinkedList(int* A, int size);

void llDisplay(LinkedList* ll);

const int* llFront(LinkedList* ll);

const int* llBack(LinkedList* ll);

void llInsert(LinkedList* ll, int index, int value);

int llDelete(LinkedList* ll, int index);

void llPopFront(LinkedList* ll);

void llPushFront(LinkedList* ll, int value);

void llPushBack(LinkedList* ll, int value);

void llDestroy(LinkedList* ll);

void llReverse(LinkedList* ll);

#endif