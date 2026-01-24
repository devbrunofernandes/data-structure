#include <stdbool.h>
#include <stddef.h>

#include "Core/LinkedLists/LinkedList.h"
#include "Core/Queue/QueueLinked.h"

#include <stdlib.h>

typedef struct QueueLinked {
    LinkedList* ll;
    int size;
} QueueLinked;

static bool isEmpty(QueueLinked* q) {
    if(q->size == 0)
        return true;
    return false;
}

void lqEnqueue(QueueLinked* q, int x) {
    llPushBack(q->ll, x);
    q->size++;
}

void lqDequeue(QueueLinked* q) {
    if(isEmpty(q)) return;

    llPopFront(q->ll);
    q->size--;
}

void lqDisplay(QueueLinked* q) {
    llDisplay(q->ll);
}

const int* lqFront(QueueLinked *q) {
    if (q->size == 0) return NULL;

    return llFront(q->ll);
}

void lqDestroy(QueueLinked *q) {
    llDestroy(q->ll);
    free(q);
}

QueueLinked* lqCreate() {
    QueueLinked* q = (QueueLinked*) malloc(sizeof(QueueLinked));
    q->ll = llCreate();
    q->size = 0;
    return q;
}