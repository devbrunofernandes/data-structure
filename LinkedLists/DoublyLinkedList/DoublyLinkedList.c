#include <stdlib.h>
#include <stdio.h>
#include "DoublyLinkedList.h"

DoublyLinkedList* arrayToLinkedList(int* A, int size) {

    DoublyLinkedList* ll = (DoublyLinkedList*) malloc(sizeof(DoublyLinkedList));
    Node *t;

    if (size <= 0) {
        ll->first = ll->last = NULL;
        ll->length = 0;
        return ll;
    }

    ll->first = (Node *) malloc(sizeof(Node));
    ll->first->data = A[0];
    ll->first->prev = NULL;
    ll->first->next = NULL;
    ll->last = ll->first;
    ll->length = 1;

    for(int i = 1; i < size; i++) {

        t = (Node *) malloc(sizeof(Node));
        t->data = A[i];
        t->next = NULL;
        t->prev = ll->last;
        ll->last->next = t;
        ll->last = t;
        ll->length++;
    }

    return ll;
}

void print(DoublyLinkedList* ll) {

    Node* p = ll->first;

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

int front(DoublyLinkedList* ll) {

    if (ll == NULL || ll->first == NULL) {
        fprintf(stderr, "Fatal Error: Attempted to access front of an empty or NULL list.\n");
        exit(EXIT_FAILURE);
    }
    return ll->first->data;
}

int back(DoublyLinkedList* ll) {

    if (ll == NULL || ll->first == NULL) {
        fprintf(stderr, "Fatal Error: Attempted to access back of an empty or NULL list.\n");
        exit(EXIT_FAILURE);
    }

    return ll->last->data;
}

void insert(DoublyLinkedList* ll, int index, int value)
{
    Node *t, *p = ll->first;
    
    if(index < 0 || index > ll->length) return;

    if(index == 0) {

        t = (Node *) malloc(sizeof(Node));
        t->data = value;
        t->prev = NULL;
        t->next = ll->first;
        if (ll->first) ll->first->prev = t;
        ll->first = t;

    } else {

        for(int i = 0; i < index - 1; i++)
            p=p->next;

        t = (Node *) malloc(sizeof(Node));
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

int erase(DoublyLinkedList* ll, int index)
{
    int x = -1;
    Node* p = ll->first;

    if(index < 1 || index > ll->length) return x;

    if(index==1) {

        ll->first = ll->first->next;
        if(ll->first) ll->first->prev = NULL;

        x = p->data;
        free(p);
    } else {

        for(int i = 0; i < index - 1; i++)
            p = p->next;

        p->prev->next = p->next;
        if(p->next)
            p->next->prev = p->prev;
        else
            ll->last = p->prev;

        x = p->data;
        free(p);
    }

    ll->length--;
    return x;
}

void popFront(DoublyLinkedList* ll) {
    if (ll->first == NULL) return;

    Node* p = ll->first;

    ll->first = p->next;
    if (ll->first) ll->first->prev = NULL;
    else ll->last = NULL;
    
    free(p);

    ll->length--;
}

void pushFront(DoublyLinkedList* ll, const int value) {
    
    Node* p = (Node*) malloc(sizeof(Node));
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

void popBack(DoublyLinkedList* ll) {
    if (ll->first == NULL) return;

    Node* p = ll->last;

    if (ll->first == ll->last) {
        ll->first = ll->last = NULL;
    } else {
        ll->last = ll->last->prev;
        ll->last->next = NULL;
    }

    free(p);

    ll->length--;
}

void pushBack(DoublyLinkedList* ll, const int value) {
    
    Node* p = (Node*) malloc(sizeof(Node));
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

void freeList(DoublyLinkedList* ll) {
    if (ll == NULL) return;

    Node* current = ll->first;
    Node* nextNode;

    while (current) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(ll);
}

int main() {

    int A[] = {10,20,30,40,50};
    DoublyLinkedList* ll = arrayToLinkedList(A, 5);

    insert(ll, 2, 25);

    printf("length is %d\n", ll->length);
    print(ll);

    freeList(ll);

    return 0;
}