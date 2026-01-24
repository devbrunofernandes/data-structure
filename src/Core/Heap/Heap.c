#include "Core/Heap.h"
#include <stdlib.h>

void heapDestroy(Heap* h) {
    if (h == NULL) return;

    free(h->array);
    free(h);
}

Heap* heapInitialize(const int maxSize) {
    Heap* h = (Heap *) malloc(sizeof(Heap));

    h->array = (int *) malloc(sizeof(int) * maxSize);
    h->maxSize = maxSize;
    h->size = 0;

    return h;
}