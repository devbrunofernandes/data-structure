/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is NOT Adaptive - can NOT easily sort an almost sorted list or stop if list became sorted in the middle of processing. Always O(n^2)
    Is NOT Stable - Can NOT keep the current order of same weight elements.

    Can be used to sort only a section of list - with 3 passes the list will have 3 smallest elements in the beginning.
    Can be used for minimum write in memory - only writes the element in his final place of the list. O(n) writes in memory.
*/

#include "Algorithms/Sorting.h"

static void pass(int* array, const int size, const int index) {

    int minor = index;

    for (int i = index + 1; i < size; i++) {
        if (array[i] < array[minor]) minor = i;
    }

    int temp = array[index];
    array[index] = array[minor];
    array[minor] = temp;
}

void selectionSort(int* array, const int size) {

    for (int i = 0; i < size - 1; i++)
        pass(array, size, i);
}