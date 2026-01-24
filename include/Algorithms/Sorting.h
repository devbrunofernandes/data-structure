#ifndef SORTING_H
#define SORTING_H

#include "Core/LinkedLists/LinkedList.h"

void binSort(int* array, int size);

void bubbleSort(int* array, int size);

void bucketSort(int* array, int size);

void bucketSortWithBuckets(int* array, int size, int bucketsQtd);

void countSort(int* array, int size);

void heapSort(int* array, int size);

void insertionSortArray(int* array, int size);

void insertInSortedPositionArray(int* array, int size, int key);

void insertInSortedPositionLinked(LinkedList* ll, LinkedListNode* key);

void insertionSortLinked(LinkedList* ll);

void iterativeMergeSort(int* array, int size);

void recursiveMergeSort(int* array, int size);

void quickSort(int* array, int size);

void radixSort(int* array, int size);

void selectionSort(int* array, int size);

void shellSort(int* array, int size);

#endif