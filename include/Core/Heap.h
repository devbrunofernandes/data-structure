#ifndef DATASTRUCTURES_HEAP_H
#define DATASTRUCTURES_HEAP_H

typedef struct Heap {
    int *array;
    int size;
    int maxSize;
} Heap;

Heap* heapInitialize(int maxSize);

void heapDestroy(Heap* h);

// Min Heap
void minHeapInsert(Heap* h, int key);

int minHeapDelete(Heap* h);

Heap* minHeapify(int* array, int size);

// Max Heap
void maxHeapInsert(Heap* h, int key);

int maxHeapDelete(Heap* h);

Heap* maxHeapify(int* array, int size);

#endif //DATASTRUCTURES_HEAP_H