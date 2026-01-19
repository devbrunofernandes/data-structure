/*
    Time complexity: O(n + k) - k is the range between min and max value in list.
    Space complexity: O(n + k) - high memory use.
    Is NOT Adaptive - can NOT easily sort an almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Its non-comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../LinkedLists/SinglyLinkedList/LinkedList.h"
#include "headers/InsertionSortLinked.h"

typedef struct MinMax {
    int min;
    int max;
} MinMax;

void printArray(const int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

MinMax findMinMax(const int* array, const int size) {
    int min = array[0];
    int max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
    }
        
    MinMax result;
    result.max = max;
    result.min = min;

    return result;
}

void bucketSortWithBuckets(int* array, const int size, const int bucketsQtd) {

    const MinMax mm = findMinMax(array, size);

    const int min = mm.min;
    const int max = mm.max;

    if (min == max) return;

    LinkedList** buckets = (LinkedList**) calloc(bucketsQtd, sizeof(LinkedList*));

    for (int i = 0; i < size; i++) {
        int index = ((array[i] - min) * (bucketsQtd - 1)) / (max - min);

        if (!buckets[index]) {
            buckets[index] = (LinkedList*) malloc(sizeof(LinkedList));
            buckets[index]->first = buckets[index]->last = NULL;
            buckets[index]->length = 0;
        }

        pushBack(buckets[index], array[i]);
    }

    for (int i = 0; i < bucketsQtd; i++)
        if (buckets[i]) insertionSort(buckets[i]);


    int arrayIndex = 0;

    for (int i = 0; i < bucketsQtd; i++) {
        if (!buckets[i]) continue;

        Node* curr = buckets[i]->first;
        while (curr) {
            array[arrayIndex++] = curr->data;
            curr = curr->next;
        }

        freeList(buckets[i]);
    }

    free(buckets);
}

void bucketSort(int* array, const int size) {

    const int bucketsQtd = size / 2;

    bucketSortWithBuckets(array, size, bucketsQtd);
}   

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    bucketSort(array, size);

    printf("Array after sort:  ");
    printArray(array, size);

    return 0;
}