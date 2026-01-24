#include <stdlib.h>
#include <stdio.h>

#include "Core/LinkedLists/DoublyLinkedList.h"

typedef struct DoublyLinkedList {
    DoublyLinkedNode* first;
    DoublyLinkedNode* last;
    int length;
} DoublyLinkedList;

DoublyLinkedList* dllCreate() {
    DoublyLinkedList* ll = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    ll->first = NULL;
    ll->last = NULL;
    ll->length = 0;
    return ll;
}

DoublyLinkedList* arrayToDoublyLinkedList(int* A, int size) {

    DoublyLinkedList* ll = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    DoublyLinkedNode *t;

    if (size <= 0) {
        ll->first = ll->last = NULL;
        ll->length = 0;
        return ll;
    }

    ll->first = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
    ll->first->data = A[0];
    ll->first->prev = NULL;
    ll->first->next = NULL;
    ll->last = ll->first;
    ll->length = 1;

    for(int i = 1; i < size; i++) {

        t = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
        t->data = A[i];
        t->next = NULL;
        t->prev = ll->last;
        ll->last->next = t;
        ll->last = t;
        ll->length++;
    }

    return ll;
}

void dllDisplay(DoublyLinkedList* ll) {

    DoublyLinkedNode* p = ll->first;

    printf("[");

    while(p->next) {
        printf("%d, ", p->data);
        p = p->next;
    }

    if (p) {
        printf("%d", p->data);
    }

    printf("]\n");
}

const int* dllFront(DoublyLinkedList* ll) {

    if (ll == NULL || ll->first == NULL) {
        return NULL;
    }
    return &(ll->first->data);
}

const int* dllBack(DoublyLinkedList* ll) {

    if (ll == NULL || ll->last == NULL) {
        return NULL;
    }

    return &(ll->last->data);
}

void dllInsert(DoublyLinkedList* ll, int index, int value)
{
    DoublyLinkedNode *t, *p = ll->first;
    
    if(index < 0 || index > ll->length) return;

    if(index == 0) {

        t = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
        t->data = value;
        t->prev = NULL;
        t->next = ll->first;
        if (ll->first) ll->first->prev = t;
        ll->first = t;

    } else {

        for(int i = 0; i < index - 1; i++)
            p=p->next;

        t = (DoublyLinkedNode *) malloc(sizeof(DoublyLinkedNode));
        t->data = value;

        t->prev = p;
        t->next = p->next;
        if(p->next)
            p->next->prev = t;
        p->next = t;

        if (p == ll->last) ll->last = t;
    }

    ll->length++;
}

void dllDelete(DoublyLinkedList* ll, int index)
{
    DoublyLinkedNode* p = ll->first;

    if(index < 1 || index > ll->length) return;

    if(index==1) {

        ll->first = ll->first->next;
        if(ll->first) ll->first->prev = NULL;

        free(p);
    } else {

        for(int i = 0; i < index - 1; i++)
            p = p->next;

        p->prev->next = p->next;
        if(p->next)
            p->next->prev = p->prev;
        else
            ll->last = p->prev;

        free(p);
    }

    ll->length--;
}

void dllPopFront(DoublyLinkedList* ll) {
    if (ll->first == NULL) return;

    DoublyLinkedNode* p = ll->first;

    ll->first = p->next;
    if (ll->first) ll->first->prev = NULL;
    else ll->last = NULL;
    
    free(p);

    ll->length--;
}

void dllPushFront(DoublyLinkedList* ll, const int value) {
    
    DoublyLinkedNode* p = (DoublyLinkedNode*) malloc(sizeof(DoublyLinkedNode));
    p->data = value;

    p->prev = NULL;
    p->next = ll->first;

    if (ll->first == NULL) {
        ll->first = p;
        ll->last = p;
    } else {
        ll->first->prev = p;
        ll->first = p;
    }

    ll->length++;
}

void dllPopBack(DoublyLinkedList* ll) {
    if (ll->first == NULL) return;

    DoublyLinkedNode* p = ll->last;

    if (ll->first == ll->last) {
        ll->first = ll->last = NULL;
    } else {
        ll->last = ll->last->prev;
        ll->last->next = NULL;
    }

    free(p);

    ll->length--;
}

void dllPushBack(DoublyLinkedList* ll, const int value) {
    
    DoublyLinkedNode* p = (DoublyLinkedNode*) malloc(sizeof(DoublyLinkedNode));
    p->data = value;
    p->next = NULL;

    if (ll->first == NULL) {
        ll->first = ll->last = p;
        p->prev = NULL;
    } else {
        p->prev = ll->last;
        ll->last->next = p;
        ll->last = p;
    }

    ll->length++;
}

void dllDestroy(DoublyLinkedList* ll) {
    if (ll == NULL) return;

    DoublyLinkedNode* current = ll->first;
    DoublyLinkedNode* nextNode;

    while (current) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(ll);
}

void dllReverse(DoublyLinkedList* dll) {

    DoublyLinkedNode* p = dll->first;

    while(p)
    {
        DoublyLinkedNode* temp = p->next;
        p->next = p->prev;
        p->prev = temp;

        p = p->prev;
        if(p && p->next == NULL)
            dll->first = p;
    }
}