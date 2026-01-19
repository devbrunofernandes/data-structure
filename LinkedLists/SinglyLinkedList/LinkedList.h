#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {

    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {

    struct Node* first;
    struct Node* last;
    int length;
} LinkedList;

LinkedList* arrayToLinkedList(int* A, int size);

void print(LinkedList* ll);

int front(LinkedList* ll);

int back(LinkedList* ll);

void insert(LinkedList* ll, int index, int value);

int erase(LinkedList* ll, int index);

void popFront(LinkedList* ll);

void pushFront(LinkedList* ll, const int value);

void pushBack(LinkedList* ll, const int value);

void freeList(LinkedList* ll);

#endif