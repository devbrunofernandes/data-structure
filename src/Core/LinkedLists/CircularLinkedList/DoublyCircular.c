#include <stdlib.h>
#include <stdio.h>
#include "Core/LinkedLists/DoublyLinkedList.h"

#include "Core/LinkedLists/DoublyCircularLinkedList.h"

typedef struct DoublyCircularLinkedList {
    DoublyLinkedNode* head;
    DoublyLinkedNode* tail;
    int length;
} DoublyCircularLinkedList;

DoublyCircularLinkedList* arrayToDoublyCircularLinkedList(int* A, int size) {
    DoublyCircularLinkedList* dcl = (DoublyCircularLinkedList*) malloc(sizeof(DoublyCircularLinkedList));

    dcl->head = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
    dcl->head->data = A[0];
    dcl->head->next = dcl->head;
    dcl->head->prev = dcl->head;
    dcl->tail = dcl->head;
    dcl->length = 1;

    for (int i = 1; i < size; i++) {
        DoublyLinkedNode* p = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
        p->data = A[i];
        p->next = dcl->tail->next;
        p->prev = dcl->tail;

        dcl->head->prev = p;
        dcl->tail->next = p;
        dcl->tail = p;
        dcl->length++;
    }

    return dcl;
}

DoublyCircularLinkedList* dclCreate() {
    DoublyCircularLinkedList* dcl = (DoublyCircularLinkedList*) malloc(sizeof(DoublyCircularLinkedList));
    dcl->head = NULL;
    dcl->tail = NULL;
    dcl->length = 0;
    return dcl;
}

void dclPrint(DoublyCircularLinkedList* dcl) {
    if (!dcl || !dcl->head) return;
    DoublyLinkedNode* p = dcl->head;

    do {
        printf("%d ", p->data);
        p = p->next;
    } while (p != dcl->head);

    printf("\n");
}

void dclDelete(DoublyCircularLinkedList* dcl, int index) {
    if (dcl == NULL || dcl->length == 0) return;

    DoublyLinkedNode* p = dcl->head;
    index = ((index % dcl->length) + dcl->length) % dcl->length;

    for (int i = 0; i < index; i++) p = p->next;

    if (dcl->length == 1) {
        dcl->head = NULL;
        dcl->tail = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (p == dcl->tail) dcl->tail = p->prev;
        if (p == dcl->head) dcl->head = p->next;
    }

    free(p);
    dcl->length--;
}

void dclInsert(DoublyCircularLinkedList* dcl, int index, const int x) {
    if (dcl->length == 0)
        index = 0;
    else
        index = ((index % dcl->length) + dcl->length) % dcl->length;

    DoublyLinkedNode* p = dcl->head;
    DoublyLinkedNode* t = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
    t->data = x;

    if(index==0) {
        if(dcl->head) {
            t->next = dcl->head;
            t->prev = dcl->head->prev;

            dcl->head->prev->next = t;
            dcl->head->prev = t;
        } else {
            t->prev = t;
            t->next = t;
        }

        dcl->head = t;
    } else {
        for(int i=0; i<index-1; i++)
            p=p->next;

        t->next = p->next;
        t->prev = p;
        if(p->next)
            p->next->prev = t;
        p->next = t;

        if (p == dcl->tail) dcl->tail = t;
    }
    dcl->length++;
}

const int* dclSearch(DoublyCircularLinkedList* dcl, const int x) {
    DoublyLinkedNode* p = dcl->head;

    do {
        if (p->data == x) return &(p->data);
        p = p->next;
    } while (p != dcl->head);

    return NULL;
}

bool dclContains(DoublyCircularLinkedList* dcl, const int x) {
    DoublyLinkedNode* p = dcl->head;

    do {
        if (p->data == x) return true;
        p = p->next;
    } while (p != dcl->head);

    return false;
}

const int* dclGet(DoublyCircularLinkedList* dcl, int index) {
    index = ((index % dcl->length) + dcl->length) % dcl->length;
    DoublyLinkedNode* p = dcl->head;

    if (index < dcl->length / 2)
        for (int i = 0; i < index; i++) p = p->next;
    else
        for (int i = 0; i < dcl->length - index; i++) p = p->prev;

    return &(p->data);
}