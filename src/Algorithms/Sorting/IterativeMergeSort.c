/*
    Time complexity: O(n log n)
    Space complexity: O(n) - use extra space.
    Can be Adaptive - with one extra line can skip merge in already sorted arrays.
    Is Stable - keeps the current order of same weight elements.

    Is a good algorithm to sort a set of elements that doesn't fit in RAM (external sorting).
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

void iterativeMergeSort(int* array, const int size) {

    int* aux = (int *) malloc(sizeof(int) * size);

    for (int curr_size = 1; curr_size < size; curr_size *= 2) {

        for (int i = 0; i < size - 1; i += 2 * curr_size) {

            int low = i;
            int mid = i + curr_size - 1;
            int high = (i + 2 * curr_size - 1 < size - 1) ? (i + 2 * curr_size - 1) : (size - 1);

            if (array[mid] <= array[mid + 1]) continue; // this line is extra to make algorithm adaptive.

            if (mid < size - 1) 
                merge(array, aux, low, mid, high);
        }
    }

    free(aux);
}