/*
    Time complexity: O(d * (n + b)) - d is the digits quantity of the larger number. b is the numeric base.
    Space complexity: O(n + b)
    Is NOT Adaptive - can NOT easily sort an almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Its non-comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>
#include "../LinkedLists/SinglyLinkedList/LinkedList.h"

typedef struct MinMax {
    int min;
    int max;
} MinMax;

void printArray(int* array, const int size) {

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

void radixPass(LinkedList* ll, LinkedList** bins, const int numericBase, const int divisor) {

    Node* p = ll->first;

    for (int i = 0; i < ll->length; i++) {
        Node* next = p->next;
        int index = (p->data / divisor) % 10;

        if (bins[index]->last) bins[index]->last->next = p;
        else bins[index]->first = p;

        bins[index]->last = p;
        bins[index]->length++;

        p->next = NULL;
        p = next;
    }

    ll->first = ll->last = NULL;
    Node* tail = NULL;

    for (int i = 0; i < numericBase; i++) {
        if (bins[i]->length == 0) continue;

        if (!ll->first)
            ll->first = bins[i]->first;

        if (tail)
            tail->next = bins[i]->first;

        tail = bins[i]->last;
    }

    ll->last = tail;
    if (tail) tail->next = NULL;

    for (int i = 0; i < numericBase; i++) {
        bins[i]->last = bins[i]->first = NULL;
        bins[i]->length = 0;
    }
}

void radixSortBins(int* array, const int size, const int numericBase) {
    if (size < 2) return;

    MinMax mm = findMinMax(array, size);

    if (mm.min < 0) {
        for (int i = 0; i < size; i++)
            array[i] -= mm.min;
        mm.max -= mm.min;
    }

    LinkedList** bins = (LinkedList**) calloc(numericBase, sizeof(LinkedList*));
    LinkedList* ll = arrayToLinkedList(array, size);

    for (int i = 0; i < numericBase; i++)
        bins[i] = (LinkedList*) calloc(1, sizeof(LinkedList));

    int divisor = 1;
    while (mm.max > 0) {
        radixPass(ll, bins, numericBase, divisor);
        divisor *= 10;
        mm.max /= 10;
    }

    Node* p = ll->first;
    for (int i = 0; i < ll->length; i++) {
        array[i] = p->data;
        if (mm.min < 0) array[i] += mm.min;
        p = p->next;
    }

    for (int i = 0; i < numericBase; i++)
        free(bins[i]);

    freeList(ll);
    free(bins);
}

void radixSort(int* array, const int size) {

    radixSortBins(array, size, 10);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    radixSort(array, size);

    printf("Array after sort:  ");
    printArray(array, size);

    return 0;
}