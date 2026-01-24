/*
    Time complexity: O(n log n)
    Space complexity: O(1) - dont use extra space.
    Is NOT Adaptive - can NOT check if array is already sorted and stop the sorting.
    Is NOT Stable - can NOT keep the current order of same weight elements.

    Can be used to sort only a section of list - with 3 passes the list will have 3 greater elements in the end.

    To see heap implementation go to src/heap/ directory in this project.
*/

#include "Core/Heap.h"
#include <stdlib.h>
#include "Algorithms/Sorting.h"

void heapSort(int* array, const int size) {

    Heap* h = maxHeapify(array, size);

    for (int i = 0; i < size; i++)
        maxHeapDelete(h);

    free(h);
}