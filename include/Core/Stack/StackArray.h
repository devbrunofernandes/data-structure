#ifndef DATASTRUCTURES_STACK_ARRAY_H
#define DATASTRUCTURES_STACK_ARRAY_H

#include <stdbool.h>

typedef struct StackArray StackArray;

StackArray* staCreate(int size);

void staPush(StackArray *st, int x);

void staPop(StackArray *st);

const int* staTop(StackArray *st);

void staDisplay(StackArray* st);

void staDestroy(StackArray* st);

bool staIsEmpty(StackArray* st);

#endif //DATASTRUCTURES_STACK_ARRAY_H