#include "Core/Heap.h"
#include <stdio.h>
#include "Core/Array/Array.h"

int main() {
    Heap* h = heapInitialize(10);

    maxHeapInsert(h, 20);
    maxHeapInsert(h, 40);
    maxHeapInsert(h, 10);
    maxHeapInsert(h, 15);
    maxHeapInsert(h, 50);
    maxHeapInsert(h, 5);
    maxHeapInsert(h, 9);
    maxHeapInsert(h, 22);

    printArray(h->array, h->size);
    
    printf("Deleted from heap: %d\n", maxHeapDelete(h));
    printf("Deleted from heap: %d\n", maxHeapDelete(h));
    printf("Deleted from heap: %d\n", maxHeapDelete(h));

    printArray(h->array, h->size);
    
    heapDestroy(h);

    return 0;
}