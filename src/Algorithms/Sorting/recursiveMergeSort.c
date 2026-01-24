/*
    Time complexity: O(n log n)
    Space complexity: O(n) - use extra space.
    Can be Adaptive - with one extra line can skip merge in already sorted arrays.
    Is Stable - keeps the current order of same weight elements.

    Is a good algorithm to sort a set of elements that doesnt fit in RAM (external sorting).
    Is great with Linked Lists because of merge nature.
*/

#include <stdlib.h>
#include "Algorithms/Sorting.h"

static void merge(int* array, int* aux, int low, int mid, int high) {
    int pointerNew = low;

    int pointerA = low;
    int pointerB = mid + 1;

    while (pointerA <= mid && pointerB <= high) {
        if (array[pointerA] <= array[pointerB])
            aux[pointerNew++] = array[pointerA++];
        else
            aux[pointerNew++] = array[pointerB++];
    }

    while (pointerA <= mid) aux[pointerNew++] = array[pointerA++];

    while (pointerB <= high) aux[pointerNew++] = array[pointerB++];

    for (int i = low; i <= high; i++)
        array[i] = aux[i];
}

static void mergeSortHelper(int* array, int* aux, const int low, const int high) {

    if (low >= high) return;

    int mid = (low + high) / 2;

    mergeSortHelper(array, aux, low, mid);
    mergeSortHelper(array, aux, mid + 1, high);
    
    if (array[mid] <= array[mid + 1]) return; // this line is extra to make algorithm adaptive.

    merge(array, aux, low, mid, high);
}

void recursiveMergeSort(int* array, const int size) {

    int* aux = (int *) malloc(sizeof(int) * size);

    mergeSortHelper(array, aux, 0, size - 1);

    free(aux);
}