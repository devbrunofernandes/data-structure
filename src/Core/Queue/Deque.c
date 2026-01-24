#include <stdbool.h>
#include <stddef.h>

#include "Core/LinkedLists/DoublyLinkedList.h"
#include "Core/Queue/Deque.h"

#include <stdlib.h>

typedef struct Deque {
    DoublyLinkedList* dll;
    int size;
} Deque;

static bool isEmpty(Deque* q) {
    if(q->size == 0)
        return true;
    return false;
}

void dequePushFront(Deque* q, int x) {
    dllPushFront(q->dll, x);
    q->size++;
}

void dequePopFront(Deque* q) {
    if(isEmpty(q)) return;

    dllPopFront(q->dll);
    q->size--;
}

void dequePushBack(Deque* q, int x) {
    dllPushBack(q->dll, x);
    q->size++;
}

void dequePopBack(Deque* q) {
    if(isEmpty(q)) return;

    dllPopBack(q->dll);
    q->size--;
}

void dequeDisplay(Deque* q) {
    dllDisplay(q->dll);
}

const int* dequeFront(Deque *q) {
    if (q->size == 0) return NULL;

    return dllFront(q->dll);
}

void dequeDestroy(Deque *q) {
    dllDestroy(q->dll);
    free(q);
}

Deque* dequeCreate() {
    Deque* q = (Deque*) malloc(sizeof(Deque));
    q->dll = dllCreate();
    q->size = 0;
    return q;
}