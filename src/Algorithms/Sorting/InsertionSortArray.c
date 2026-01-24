/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sorted only needs one comparation for each element.
    Is Stable - keeps the current order of same weight elements.

    Is more friendly with Linked Lists because of insertion behavior.
    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property. 
*/

#include "Algorithms/Sorting.h"

void insertInSortedPositionArray(int* array, const int size, const int key) {
    
    int i = size - 1;

    while (i >= 0 && key < array[i]) {

        array[i + 1] = array[i];
        i--;
    }

    array[i + 1] = key;
}

void insertionSortArray(int* array, const int size) {

    for (int i = 1; i < size; i++)
        insertInSortedPositionArray(array, i, array[i]);
}