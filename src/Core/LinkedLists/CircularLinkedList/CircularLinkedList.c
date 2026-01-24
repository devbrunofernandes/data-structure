#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Core/LinkedLists/LinkedList.h"

#include "Core/LinkedLists/CircularLinkedList.h"

/* circular linked list
 * the last node points to the first node
 * 
 * Other way to represent circular linked lists is use a first no data head node
 * In this way the program can distinguish a null default list from a null circular list
 */
typedef struct CircularLinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
    int length;
} CircularLinkedList;

CircularLinkedList* arrayToCircularLinkedList(int* A, int size) {

    CircularLinkedList* cll = (CircularLinkedList*) malloc(sizeof(CircularLinkedList));

    LinkedListNode* t;
    LinkedListNode* last;

    cll->head = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    cll->head->data=A[0];
    cll->head->next = cll->head;
    cll->tail = cll->head;
    last = cll->head;
    cll->length = 1;

    for (int i=1; i< size ; i++) {
        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
        cll->tail = last;
        cll->length++;
    }

    return cll;
}

CircularLinkedList* clCreate() {
    CircularLinkedList* cll;
    cll = (CircularLinkedList*) malloc(sizeof(CircularLinkedList));
    cll->head = NULL;
    cll->tail = NULL;
    cll->length = 0;
    return cll;
}

void clPrint(CircularLinkedList* cll) {
    LinkedListNode* h = cll->head;

    do {
        printf("%d ", h->data);
        h = h->next;
    }while (h != cll->head);

    printf("\n");
}

void clDelete(CircularLinkedList *cll, int index) {
    if (cll->length == 0) return;

    LinkedListNode* p = cll->head;
    LinkedListNode *q;
    
    index = ((index % cll->length) + cll->length) % cll->length;

    if(index == 0) {
        while(p->next != cll->head) {
            p = p->next;
        }

        if(cll->head == p) {
            free(cll->head);
            cll->head = NULL;
        } else {
            p->next = cll->head->next;
            free(cll->head);
            cll->head = p->next;
        }
    } else {
        for(int i=0; i < index-1; i++)
            p = p->next;

        q = p->next;
        p->next = q->next;
        if (q == cll->tail) cll->tail = p;
        free(q);
    }
    cll->length--;
}

void clInsert(CircularLinkedList* cll, int index, int x) {
    LinkedListNode *p = cll->head;
    LinkedListNode *t;

    index = ((index % cll->length) + cll->length) % cll->length;

    if(index==0) {
        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = x;

        if(cll->head == NULL) {
            cll->head = t;
            cll->head->next = cll->head;
        } else {
            while(p->next != cll->head) {
                p=p->next;
            }

            p->next = t;
            t->next = cll->head;
            cll->head = t;
        }
    } else {
        for(int i=0; i<index-1; i++) {
            p=p->next;
        }

        t = (LinkedListNode *) malloc(sizeof(LinkedListNode));
        t->data = x;
        t->next = p->next;
        p->next = t;
    }
    cll->length++;
}

void clDestroy(CircularLinkedList* cll) {
    LinkedListNode* p = cll->head->next;

    while (p != cll->head) {
        LinkedListNode* deletedNode = p;
        p = p->next;
        free(deletedNode);
    }
    free(cll->head);
    free(cll);
}

const int* clSearch(CircularLinkedList* cll, int x) {
    LinkedListNode* p = cll->head;

    do {
        if (p->data == x) return &(p->data);
        p = p->next;
    } while (p != cll->head);

    return NULL;
}

bool clContains(CircularLinkedList* cll, int x) {
    LinkedListNode* p = cll->head;

    do {
        if (p->data == x) return true;
        p = p->next;
    } while (p != cll->head);

    return false;
}

const int* clGet(CircularLinkedList* cll, int index) {
    if (cll->length == 0) return NULL;

    LinkedListNode* p = cll->head;

    index = ((index % cll->length) + cll->length) % cll->length;

    for (int i = 0; i < index; i++) {
        p = p->next;
    }

    return &(p->data);
}
