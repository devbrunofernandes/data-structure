#include <stdlib.h>
#include "Core/Heap.h"

static void siftDown(Heap* h, const int index) {
    int current = index;
    const int size = h->size;

    while (1) {
        const int left = 2 * current + 1;
        const int right = 2 * current + 2;
        int smallest = current;

        if (left < size && h->array[left] < h->array[smallest])
            smallest = left;

        if (right < size && h->array[right] < h->array[smallest])
            smallest = right;

        if (smallest == current) break;

        const int temp = h->array[current];
        h->array[current] = h->array[smallest];
        h->array[smallest] = temp;

        current = smallest;
    }
}

void minHeapInsert(Heap* h, const int key) {
    if (h->size == h->maxSize) return;

    int i = h->size;

    h->array[i] = key;
    h->size++;

    const int temp = h->array[i];

    while (i > 0 && temp < h->array[i / 2]) {
        h->array[i] = h->array[i / 2];
        i = i / 2;
    }

    h->array[i] = temp;
}

int minHeapDelete(Heap* h) {
    if (h->size == 0) return -1;

    const int deletedKey = h->array[0];

    h->array[0] = h->array[h->size - 1];
    h->array[h->size - 1] = deletedKey;
    h->size--;

    siftDown(h, 0);

    return deletedKey;
}

Heap* minHeapify(int* array, const int size) {
    Heap* h = (Heap*) malloc(sizeof(Heap));
    h->array = array;
    h->size = size;
    h->maxSize = size;

    for (int i = (size / 2) - 1; i >= 0; i--)
        siftDown(h, i);

    return h;
}