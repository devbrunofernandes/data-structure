#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Core/LinkedLists/DoublyLinkedList.h"

#include "Core/Stack/StackLinked.h"

typedef struct StackLinked {
    DoublyLinkedList* dll;
    int size;
} StackLinked;

bool stlIsEmpty(StackLinked* st) {
    if(st->size == 0)
        return true;
    return false;
}

void stlPush(StackLinked *st, int x) {
    dllPushBack(st->dll, x);
    st->size++;
}

void stlPop(StackLinked *st) {
    if (stlIsEmpty(st)) return;

    dllPopBack(st->dll);
    st->size--;
}

void stlDisplay(StackLinked* st) {
    dllDisplay(st->dll);
}

const int* stlTop(StackLinked* st) {
    if(stlIsEmpty(st)) return NULL;

    return dllBack(st->dll);
}

void stlDestroy(StackLinked* st) {
    dllDestroy(st->dll);
    free(st);
}

StackLinked* stlCreate() {
    StackLinked* st = (StackLinked*) malloc(sizeof(StackLinked));
    st->size = 0;
    st->dll = dllCreate();
    return st;
}