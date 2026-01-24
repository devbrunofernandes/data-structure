/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Can be Adaptive - can check if array is already sorted and stop the sorting.
    Is Stable - keeps the current order of same weight elements.

    Can be used to sort only a section of list - with 3 passes the list will have 3 greater elements in the end.
*/
#include "Algorithms/Sorting.h"

static int pass(int* array, const int size, const int sorted) {
    
    int limit = size - sorted - 1;
    int swapHappened = 0;

    for (int i = 0; i < limit; i++) {
        if (array[i] > array[i + 1]) {
            int temp = array[i];
            array[i] = array[i + 1];
            array[i + 1] = temp;

            swapHappened = 1;
        }
    }

    return swapHappened;
}

void bubbleSort(int* array, const int size) {

    int swapHappened = 0;

    for (int i = 0; i < size - 1; i++) {
        swapHappened = pass(array, size, i);

        if (!swapHappened) break;
    }
}