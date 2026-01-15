/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sorted only needs one comparation for each element.
    Is Stable - keeps the current order of same weight elements.

    Is more friendly with Linked Lists because of insertion behavior.
    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property. 
*/

#include <stdio.h>

void printArray(int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

void insertInSortedPosition(int* array, const int size, const int key) {
    
    int i = size - 1;

    while (i >= 0 && key < array[i]) {

        array[i + 1] = array[i];
        i--;
    }

    array[i + 1] = key;
}

void insertionSort(int* array, const int size) {

    for (int i = 1; i < size; i++)
        insertInSortedPosition(array, i, array[i]);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    insertionSort(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}