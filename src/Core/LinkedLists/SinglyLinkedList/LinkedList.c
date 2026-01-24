#include <stdlib.h>
#include <stdio.h>

#include "Core/LinkedLists/LinkedList.h"

LinkedList* llCreate() {
    LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
    ll->first = NULL;
    ll->last = NULL;
    ll->length = 0;
    return ll;
}

LinkedList* arrayToLinkedList(int* A, int size) {

    LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
    LinkedListNode *t;

    if (size <= 0) {
        ll->first = ll->last = NULL;
        ll->length = 0;
        return ll;
    }

    ll->first = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    ll->first->data = A[0];

    ll->first->next = NULL;
    ll->last = ll->first;
    ll->length = 1;

    for(int i = 1; i < size; i++) {

        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = A[i];
        t->next = NULL;

        ll->last->next = t;
        ll->last = t;
        ll->length++;
    }

    return ll;
}

void llDisplay(LinkedList* ll) {

    LinkedListNode* p = ll->first;

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

const int* llFront(LinkedList* ll) {

    if (ll == NULL || ll->first == NULL) {
        return NULL;
    }
    return &(ll->first->data);
}

const int* llBack(LinkedList* ll) {
    
    if (ll == NULL || ll->last == NULL) {
        return NULL;
    }

    return &(ll->last->data);
}

void llInsert(LinkedList* ll, int index, int value)
{
    LinkedListNode *t, *p = ll->first;
    
    if(index < 0 || index > ll->length) return;

    if(index == 0) {

        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = value;
        t->next = ll->first;
        ll->first = t;

    } else {

        for(int i = 0; i < index - 1; i++)
            p=p->next;

        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = value;

        t->next = p->next;
        p->next = t;

        if (p == ll->last) ll->last = t;
    }

    ll->length++;
}

int llDelete(LinkedList* ll, int index)
{
    int x = -1;
    LinkedListNode* p = ll->first;

    if(index < 1 || index > ll->length) return x;

    if(index==1) {

        ll->first = ll->first->next;
        if (ll->last == p) ll->last = NULL;

        x = p->data;
        free(p);
    } else {

        LinkedListNode* tail = NULL;

        for(int i = 0; i < index - 1; i++) {
            tail = p;
            p = p->next;
        }

        tail->next = p->next;
        if (ll->last == p) ll->last = tail;

        x = p->data;
        free(p);
    }

    ll->length--;
    return x;
}

void llPopFront(LinkedList* ll) {
    if (ll->first == NULL) return;

    LinkedListNode* p = ll->first;
    
    if (ll->last == ll->first) ll->last = NULL;
    ll->first = p->next;
    
    free(p);

    ll->length--;
}

void llPushFront(LinkedList* ll, const int value) {
    
    LinkedListNode* p = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    p->data = value;

    p->next = ll->first;

    if (ll->first == NULL) ll->last = p;

    ll->first = p;

    ll->length++;
}

void llPushBack(LinkedList* ll, const int value) {
    
    LinkedListNode* p = (LinkedListNode*) malloc(sizeof(LinkedListNode));
    p->data = value;
    p->next = NULL;

    if (!ll->first)
        ll->first = p;
    else
        ll->last->next = p;
    
    ll->last = p;

    ll->length++;
}

void llDestroy(LinkedList* ll) {
    if (ll == NULL) return;

    LinkedListNode* current = ll->first;
    LinkedListNode* nextNode;

    while (current) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(ll);
}

void llReverse(LinkedList* ll) {
    LinkedListNode* p = ll->first;
    LinkedListNode* q = NULL;
    LinkedListNode* r = NULL;

    ll->last = p;

    while (p) {
        // Sliding pointers algorithm
        r = q;
        q = p;
        p = p->next;
        // ===========================
        q->next = r;
    }

    ll->first = q;
}