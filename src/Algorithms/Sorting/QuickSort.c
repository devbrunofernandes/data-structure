/*
    Time complexity: O(n log n)
    Space complexity: O(log n) - use space for recursive functions call.
    Is NOT Adaptive - can NOT easily sort a almost sorted list or stop if list became sorted in the middle of processing.
    Is NOT Stable - Can NOT keep the current order of same weight elements.

    Worst case scenario O(n^2) typically when list is already sorted but depends on pivot choose.
*/

#include "Algorithms/Sorting.h"

static void swap(int* a, int* b) {

    const int temp = *a;
    *a = *b;
    *b = temp;
}

// technique to choose better pivots
static int choosePivot(int* array, const int low, const int high) {

    int left = low;
    int middle = ((high - low) / 2) + low;
    int right = high;

    if (array[left] >= array[middle] && array[left] <= array[high])
        return left;

    if (array[middle] >= array[left] && array[middle] <= array[high])
        return middle;

    return right;
}

static int partition(int* array, const int low, const int high) {

    int pivotIndex = choosePivot(array, low, high);
    int pivotValue = array[pivotIndex];
    if (pivotValue != array[low]) swap(&array[low], &array[pivotIndex]);

    int left = low;
    int right = high;

    do {

        do left++; while (left < high && array[left] <= pivotValue );

        do right--; while (array[right] > pivotValue );

        if (left < right)
            swap(&array[left], &array[right]);

    } while (left < right);

    swap(&array[low], &array[right]);

    return right;
}

static void quickSortHelper(int* array, const int low, const int high) {

    if (low >= high) return;

    int pos = partition(array, low, high);

    quickSortHelper(array, low, pos);
    quickSortHelper(array, pos + 1, high);
}


void quickSort(int* array, const int size) {

    quickSortHelper(array, 0, size);
}