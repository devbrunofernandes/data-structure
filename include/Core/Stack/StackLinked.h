#ifndef DATASTRUCTURES_STACK_LINKED_H
#define DATASTRUCTURES_STACK_LINKED_H

#include <stdbool.h>

typedef struct StackLinked StackLinked;

StackLinked* stlCreate();

void stlPush(StackLinked *st, int x);

void stlPop(StackLinked *st);

const int* stlTop(StackLinked *st);

void stlDisplay(StackLinked* st);

void stlDestroy(StackLinked* st);

bool stlIsEmpty(StackLinked* st);

#endif //DATASTRUCTURES_STACK_LINKED_H