#ifndef DATASTRUCTURES_QUEUE_ARRAY_H
#define DATASTRUCTURES_QUEUE_ARRAY_H

typedef struct QueueArray QueueArray;

QueueArray* aqCreate(int size);

void aqEnqueue(QueueArray *q, int x);

void aqDequeue(QueueArray *q);

void aqPrint(QueueArray *q);

int* aqFront(QueueArray *q);

void aqDestroy(QueueArray *q);

#endif //DATASTRUCTURES_QUEUE_ARRAY_H