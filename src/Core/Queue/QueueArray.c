#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Core/Queue/QueueArray.h"

/*
    Circular queue is the best way to implement queue using array
    It prevents the waste of spacing caused by two pointers method
    The total numbers of elements that can be inserted into the circular queue is equal to the size of array - 1
 */

typedef struct QueueArray {
    int size;
    int front;
    int rear;
    int *q;
} QueueArray;

QueueArray* aqCreate(const int size) {
    QueueArray *q = (QueueArray *) malloc(sizeof(QueueArray));

    q->size = size;
    q->front = q->rear = 0;
    q->q = (int *) malloc(sizeof(int) * size);

    return q;
}

static bool isEmpty(QueueArray *q) {
    if(q->rear == q->front)
        return true;
    return false;
}

static bool isFull(QueueArray *q) {
    if((q->rear + 1) % q->size == q->front)
        return true;
    return false;
}

void aqEnqueue(QueueArray *q, int x) {
    if(!isFull(q)) {
        q->rear = (q->rear + 1) % q->size;
        q->q[q->rear] = x;
    }
}

void aqDequeue(QueueArray *q) {
    if(!isEmpty(q)) {
        q->front = (q->front + 1) % q->size;
    }
}

int* aqFront(QueueArray *q) {
    if (isEmpty(q)) return NULL;

    return &(q->q[q->front]);
}

void aqDestroy(QueueArray *q) {
    free(q->q);
    free(q);
}

void aqPrint(QueueArray *q) {
    int i = q->front + 1;
    do {
        printf("%d ", q->q[i]);
        i = (i + 1) % q->size;
    } while(i != (q->rear + 1) % q->size);

    printf("\n");
}