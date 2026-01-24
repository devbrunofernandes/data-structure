#ifndef DATASTRUCTURES_DEQUE_H
#define DATASTRUCTURES_DEQUE_H

typedef struct Deque Deque;

Deque* dequeCreate();

void dequePushFront(Deque *q, int x);

void dequePopFront(Deque *q);

void dequePushBack(Deque *q, int x);

void dequePopBack(Deque *q);

void dequeDisplay(Deque *q);

const int* dequeFront(Deque *q);

const int* dequeBack(Deque *q);

void lqDestroy(Deque *q);

#endif //DATASTRUCTURES_DEQUE_H