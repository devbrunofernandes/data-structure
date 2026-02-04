#include <stdbool.h>
#include <stddef.h>

#include "Core/LinkedLists/LinkedList.h"
#include "Core/Queue/QueueLinked.h"

#include <stdlib.h>

typedef struct QueueLinked {
    LinkedList* ll;
    int size;
} QueueLinked;

bool isEmptyLinkedQueue(const QueueLinked* q) {
    if(q->size == 0)
        return true;
    return false;
}

void enqueueLinkedQueue(QueueLinked* q, const int x) {
    llPushBack(q->ll, x);
    q->size++;
}

void dequeueLinkedQueue(QueueLinked* q) {
    if(isEmptyLinkedQueue(q)) return;

    llPopFront(q->ll);
    q->size--;
}

void displayLinkedQueue(QueueLinked* q) {
    llDisplay(q->ll);
}

const int* frontLinkedQueue(QueueLinked *q) {
    if (q->size == 0) return NULL;

    return llFront(q->ll);
}

void destroyLinkedQueue(QueueLinked *q) {
    llDestroy(q->ll);
    free(q);
}

QueueLinked* createLinkedQueue() {
    QueueLinked* q = (QueueLinked*) malloc(sizeof(QueueLinked));
    q->ll = llCreate();
    q->size = 0;
    return q;
}