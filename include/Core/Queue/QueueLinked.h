#ifndef DATASTRUCTURES_QUEUE_LINKED_H
#define DATASTRUCTURES_QUEUE_LINKED_H

typedef struct QueueLinked QueueLinked;

QueueLinked* lqCreate();

void lqEnqueue(QueueLinked *q, int x);

void lqDequeue(QueueLinked *q);

void lqDisplay(QueueLinked *q);

const int* lqFront(QueueLinked *q);

void lqDestroy(QueueLinked *q);

#endif //DATASTRUCTURES_QUEUE_LINKED_H