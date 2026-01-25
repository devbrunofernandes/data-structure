#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Core/Array/Array.h"

void printArray(const int* array, const int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

MinMax findMinMax(const int* array, const int size) {
    MinMax m;
    if (size == 0) return m;

    m.min = array[0];
    m.max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] < m.min) m.min = array[i];
        if (array[i] > m.max) m.max = array[i];
    }

    return m;
}

int sumArray(const int* array, const int currentSize) {
    int total = 0;
    for (int i = 0; i <currentSize; i++) {
        total += array[i];
    }

    return total;
}

double avgArray(const int* array, const int currentSize) {
    if (currentSize == 0) return 0.0;

    return (double) sumArray(array, currentSize)/ currentSize;
}

// all elements in array MUST be sorted.
bool binarySearchArray(const int* array, const int currentSize, const int key) {
    int l = 0;
    int h = currentSize - 1;

    while (l <= h) {
        int mid = (h + l) / 2;

        if (key == array[mid]) return true;

        if (key < array[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }

    return false;
} // binary search time complexity O(log n).

bool arrayIsSorted(const int* array, const int currentSize)  {
    for (int i = 0; i < currentSize - 1; i++) {
        if (array[i] > array[i+1])
            return false;
    }

    return true;
}

void deleteArray(int* array, int* currentSize, const int index) {

    if(index < 0 || index >= *currentSize) return;

    for (int i = index; i < *currentSize - 1; i++)
        array[i] = array[i + 1];

    array[*currentSize - 1] = 0;
    (*currentSize)--;
}

void insertArray(int* array, int* currentSize,const int maxSize, const int index, const int key) {
    if (*currentSize >= maxSize) return;
    if(index < 0 || index >= maxSize) return;

    for (int i = *currentSize; i > index; i--)
        array[i] = array[i - 1];

    array[index] = key;
    (*currentSize)++;
}

void insertSortedArray(int* array, int* currentSize, const int maxSize, const int key) {
    if (*currentSize >= maxSize) return;

    int i = *currentSize - 1;

    while (i >= 0 && array[i] > key) {
        array[i + 1] = array[i];
        i--;
    }

    (*currentSize)++;
    array[i + 1] = key;
}

bool linearSearchArray(const int* array, const int currentSize, const int key) {

    for (int i = 0; i < currentSize; i++) {
        if (array[i] == key) return true;
    }

    return false;
}

int* createMergedArray(const int* array1, const int size1, const int* array2, const int size2) {
    int i=0, j=0, k=0;
    int* array3 = (int *)malloc(sizeof(int) * (size1 + size2));

    while (i < size1 && j < size2) {
        if(array1[i] < array2[j])
            array3[k++] = array1[i++];
        else
            array3[k++] = array2[j++];
    }

    for (; i < size1; i++)
        array3[k++] = array1[i];

    for (; j < size2; j++)
        array3[k++] = array2[j];

    return array3;
}

static void swap(int* x, int* y) {
    const int temp = *x;
    *x = *y;
    *y = temp;
}

void reverseArray(int* array, const int currentSize) {
    int l = 0;
    int r = currentSize - 1;

    while (l < r) {
        swap(&array[l], &array[r]);
        l++;
        r--;
    }
}

void leftRotateArray(int* array, const int currentSize) {
    if (currentSize <= 1) return;

    const int first = array[0];

    for (int i = 0; i < currentSize - 1; i++) {
        array[i] = array[i + 1];
    }

    array[currentSize - 1] = first;
}

void rightRotateArray(int* array, int currentSize) {
    if (currentSize <= 1) return;

    const int last = array[currentSize - 1];

    for (int i = currentSize- 1; i > 0; i--) {
        array[i] = array[i - 1];
    }

    array[0] = last;
}