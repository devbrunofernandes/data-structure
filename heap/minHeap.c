#include <stdio.h>
#include <stdlib.h>

struct Heap {
    int *array;
    int size;
    int maxSize;
};

void print(struct Heap* h) {
    for (int i = 0; i < h->size; i++)
        printf("%d ", h->array[i]);

    printf("\n");
}

struct Heap* heapInitialize(const int maxSize) {
    struct Heap* h = (struct Heap *) malloc(sizeof(struct Heap));

    h->array = (int *) malloc(sizeof(int) * maxSize);
    h->maxSize = maxSize;
    h->size = 0;

    return h;
} 

void heapInsert(struct Heap* h, const int key) {
    if (h->size == h->maxSize) return;

    int temp;
    int i = h->size;

    h->array[i] = key;
    h->size++;

    temp = h->array[i];

    while (i > 0 && temp < h->array[i / 2]) {
        h->array[i] = h->array[i / 2];
        i = i / 2;
    }

    h->array[i] = temp;
}

void siftDown(struct Heap* h, int index) {
    int current = index;
    int size = h->size;

    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;

        if (left < size && h->array[left] < h->array[smallest])
            smallest = left;

        if (right < size && h->array[right] < h->array[smallest])
            smallest = right;

        if (smallest == current) break;

        int temp = h->array[current]; 
        h->array[current] = h->array[smallest];
        h->array[smallest] = temp;

        current = smallest;
    }
}

int heapDelete(struct Heap* h) {
    if (h->size == 0) return -1;

    int deletedKey = h->array[0];

    h->array[0] = h->array[h->size - 1];
    h->array[h->size - 1] = deletedKey;
    h->size--;

    siftDown(h, 0);

    return deletedKey;
}

struct Heap* heapify(int* array, int size) {
    struct Heap* h = heapInitialize(size);
    h->size = size;

    for (int i = 0; i < size; i++)
         h->array[i] = array[i];

    for (int i = (size / 2) - 1; i >= 0; i--)
        siftDown(h, i);

    return h;
}

// In this case heap sort will sort and invert the array
void heapSort(int* array, int size) {
    int deleted;
    struct Heap* h = heapify(array, size);

    for (int i = 0; i < size; i++) {
        deleted = heapDelete(h);
        array[size - i - 1] = deleted;
    }
}

void heapDestroy(struct Heap* h) {
    if (h == NULL) return;

    free(h->array);
    free(h);
}

int main() {
    struct Heap* h = heapInitialize(10);

    heapInsert(h, 20);
    heapInsert(h, 40);
    heapInsert(h, 10);
    heapInsert(h, 15);
    heapInsert(h, 50);
    heapInsert(h, 5);
    heapInsert(h, 9);
    heapInsert(h, 22);

    print(h);
    
    printf("Deleted from heap: %d\n", heapDelete(h));
    printf("Deleted from heap: %d\n", heapDelete(h));
    printf("Deleted from heap: %d\n", heapDelete(h));

    print(h);



    printf("\nTesting heap sort:\n");
    int array[10] = {8, 2, 4, 5, 1, 3, 7, 10, 9, 6};
    printf("Array values before sort -> ");
    for (int i = 0; i < 10; i++)
        printf("%d ", array[i]);
    printf("\n");

    heapSort(array, 10);

    printf("Array values after sort -> ");
    for (int i = 0; i < 10; i++)
        printf("%d ", array[i]);
    printf("\n");
    
    heapDestroy(h);

    return 0;
}