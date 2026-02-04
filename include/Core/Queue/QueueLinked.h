#ifndef DATASTRUCTURES_QUEUE_LINKED_H
#define DATASTRUCTURES_QUEUE_LINKED_H

#include <stdbool.h>

typedef struct QueueLinked QueueLinked;

bool isEmptyLinkedQueue(const QueueLinked* q);

QueueLinked* createLinkedQueue();

void enqueueLinkedQueue(QueueLinked *q, int x);

void dequeueLinkedQueue(QueueLinked *q);

void displayLinkedQueue(QueueLinked *q);

const int* frontLinkedQueue(QueueLinked *q);

void destroyLinkedQueue(QueueLinked *q);

#endif //DATASTRUCTURES_QUEUE_LINKED_H