#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedList* arrayToLinkedList(int* A, int size) {

    LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList));
    Node *t;

    if (size <= 0) {
        ll->first = ll->last = NULL;
        ll->length = 0;
        return ll;
    }

    ll->first = (Node *) malloc(sizeof(Node));
    ll->first->data = A[0];

    ll->first->next = NULL;
    ll->last = ll->first;
    ll->length = 1;

    for(int i = 1; i < size; i++) {

        t = (Node *) malloc(sizeof(Node));
        t->data = A[i];
        t->next = NULL;

        ll->last->next = t;
        ll->last = t;
        ll->length++;
    }

    return ll;
}

void print(LinkedList* ll) {

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

void insert(LinkedList* ll, int index, int value)
{
    Node *t, *p = ll->first;
    
    if(index < 0 || index > ll->length) return;

    if(index == 0) {

        t = (Node *) malloc(sizeof(Node));
        t->data = value;
        t->next = ll->first;
        ll->first = t;

    } else {

        for(int i = 0; i < index - 1; i++)
            p=p->next;

        t = (Node *) malloc(sizeof(Node));
        t->data = value;

        t->next = p->next;
        p->next = t;

        if (p == ll->last) ll->last = t;
    }

    ll->length++;
}

int erase(LinkedList* ll, int index)
{
    int x = -1;
    Node* p = ll->first;

    if(index < 1 || index > ll->length) return x;

    if(index==1) {

        ll->first = ll->first->next;
        if (ll->last == p) ll->last = NULL;

        x = p->data;
        free(p);
    } else {

        Node* tail = NULL;

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

void popFront(LinkedList* ll) {
    if (ll->first == NULL) return;

    Node* p = ll->first;
    
    if (ll->last == ll->first) ll->last = NULL;
    ll->first = p->next;
    
    free(p);

    ll->length--;
}

void pushFront(LinkedList* ll, const int value) {
    
    Node* p = (Node*) malloc(sizeof(Node));
    p->data = value;

    p->next = ll->first;

    if (ll->first == NULL) ll->last = p;

    ll->first = p;

    ll->length++;
}

void pushBack(LinkedList* ll, const int value) {
    
    Node* p = (Node*) malloc(sizeof(Node));
    p->data = value;
    p->next = NULL;

    if (!ll->first)
        ll->first = p;
    else
        ll->last->next = p;
    
    ll->last = p;

    ll->length++;
}

void freeList(LinkedList* ll) {
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
    LinkedList* ll = arrayToLinkedList(A, 5);

    insert(ll, 2, 25);

    printf("length is %d\n", ll->length);
    print(ll);

    return 0;
}