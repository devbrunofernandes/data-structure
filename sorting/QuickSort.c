/*
    Time complexity: O(n log n)
    Space complexity: O(log n) - use space for recursive functions call.
    Is NOT Adaptive - can NOT easily sort a almost sorted list or stop if list became sorted in the middle of processing.
    Is NOT Stable - Can NOT keep the current order of same weight elements.

    Worst case scenario O(n^2) typically when list is already sorted but depends on pivot choose.
*/

#include <stdio.h>

void printArray(int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

void swap(int* a, int* b) {

    int temp = *a;
    *a = *b;
    *b = temp;
}

// technique to choose better pivots
int choosePivot(int* array, const int low, const int high) {

    int left = low;
    int middle = ((high - low) / 2) + low;
    int right = high;

    if (array[left] >= array[middle] && array[left] <= array[high])
        return left;
    else if (array[middle] >= array[left] && array[middle] <= array[high])
        return middle;
    else
        return right;
}

int partition(int* array, const int low, const int high) {

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

void quickSortHelper(int* array, const int low, const int high) {

    if (low >= high) return;

    int pos = partition(array, low, high);

    quickSortHelper(array, low, pos);
    quickSortHelper(array, pos + 1, high);
}


void quickSort(int* array, const int size) {

    quickSortHelper(array, 0, size);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    quickSort(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}