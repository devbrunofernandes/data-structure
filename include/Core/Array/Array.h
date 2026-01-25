#ifndef DATASTRUCTURES_ARRAY_H
#define DATASTRUCTURES_ARRAY_H

#include <stdbool.h>

typedef struct MinMax {
    int min;
    int max;
} MinMax;

void printArray(const int* array, int currentSize);

MinMax findMinMax(const int* array, int currentSize);

int sumArray(const int* array, int currentSize);

double avgArray(const int* array, int currentSize);

bool binarySearchArray(const int* array, int currentSize, int key);

bool arrayIsSorted(const int* array, int currentSize);

void deleteArray(int* array, int* currentSize, int index);

void insertArray(int* array, int* currentSize, int maxSize, int index, int key);

void insertSortedArray(int* array, int* currentSize, int maxSize, int key);

bool linearSearchArray(const int* array, int currentSize, int key);

int* createMergedArray(const int* array1, int size1, const int* array2, int size2);

void reverseArray(int* array, int currentSize);

void leftRotateArray(int* array, int currentSize);

void rightRotateArray(int* array, int currentSize);

#endif //DATASTRUCTURES_ARRAY_H