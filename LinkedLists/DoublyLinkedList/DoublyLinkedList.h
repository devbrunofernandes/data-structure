#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {

    struct Node *prev;
    int data;
    struct Node *next;
} Node;

typedef struct DoublyLinkedList {

    struct Node* first;
    struct Node* last;
    int length;
} DoublyLinkedList;

DoublyLinkedList* arrayToLinkedList(int* A, int size);

void print(DoublyLinkedList* ll);

void insert(DoublyLinkedList* ll, int index, int value);

int erase(DoublyLinkedList* ll, int index);

void popFront(DoublyLinkedList* ll);

void pushFront(DoublyLinkedList* ll, const int value);

void popBack(DoublyLinkedList* ll);

void pushBack(DoublyLinkedList* ll, const int value);

void freeList(DoublyLinkedList* ll);

#endif