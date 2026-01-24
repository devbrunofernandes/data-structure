#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Core/Stack/StackArray.h"

typedef struct StackArray {
    int size;
    int top;
    int *s;
} StackArray;

StackArray* staCreate(const int size) {
    StackArray* st = (StackArray*)malloc(sizeof(StackArray));

    st->size = size;
    st->top = -1;
    st->s = (int *) malloc(st->size * sizeof(int));

    return st;
}

bool staIsEmpty(StackArray* st) {
    if(st->top == -1)
        return true;
    return false;
}

static bool isFull(StackArray* st) {
    return st->top == st->size-1;
}

void staPush(StackArray* st, int x) {
    if(isFull(st)) return;

    st->top++;
    st->s[st->top] = x;
}

void staPop(StackArray* st) {
    if(staIsEmpty(st)) return;

    st->top--;
}

const int* staTop(StackArray* st) {
    if(staIsEmpty(st)) return NULL;

    return &(st->s[st->top]);
}

void staDisplay(StackArray* st) {
    printf("[");
    for(int i=st->top; i >= 0; i--)
    {
        if(i != 0)
            printf("%d, ", st->s[i]);
        else
            printf("%d", st->s[i]);
    }
    printf("]");
    printf("\n");
}

void staDestroy(StackArray* st) {
    free(st->s);
    free(st);
}