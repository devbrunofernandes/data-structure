/*
    Time complexity: O(n log n) or O(n^1.5)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sort the algorithm don't swap elements and do just few comparatives.
    Is NOT Stable - Can NOT keep the current order of same weight elements.

    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property.
*/

#include "Algorithms/Sorting.h"

static int knuthSequence(const int limit) {
    int n = 1;

    while (n < limit / 3)
        n = 3 * n + 1;

    return n;
}

static int shellSwap(int* array, const int firstIndex, const int secondIndex) {

    if (array[firstIndex] > array[secondIndex]) {
        int temp = array[firstIndex];
        array[firstIndex] = array[secondIndex];
        array[secondIndex] = temp;

        return 1;
    }

    return 0;
}

void shellSort(int* array, const int size) {

    int gap = knuthSequence(size);

    while (gap >= 1) {
        for (int i = gap; i < size; i++) {
            int head = i;
            int tail = head - gap;

            while (tail >= 0 && shellSwap(array, tail, head)) {
                head = tail;
                tail = head - gap;
            }
        }
        gap = (gap - 1) / 3;
    }
}