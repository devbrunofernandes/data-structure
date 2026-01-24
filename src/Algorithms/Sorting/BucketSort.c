/*
    Time complexity: O(n + k) - k is the range between min and max value in list.
    Space complexity: O(n + k) - high memory use.
    Is NOT Adaptive - can NOT easily sort an almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Its non-comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>
#include "Core/LinkedLists/LinkedList.h"
#include "Core/Array.h"
#include "Algorithms/Sorting.h"

void bucketSortWithBuckets(int* array, const int size, const int bucketsQtd) {

    const MinMax mm = findMinMax(array, size);

    const int min = mm.min;
    const int max = mm.max;

    if (min == max) return;

    LinkedList** buckets = (LinkedList**) calloc(bucketsQtd, sizeof(LinkedList*));

    for (int i = 0; i < size; i++) {
        int index = ((array[i] - min) * (bucketsQtd - 1)) / (max - min);

        if (!buckets[index]) {
            buckets[index] = (LinkedList*) malloc(sizeof(LinkedList));
            buckets[index]->first = buckets[index]->last = NULL;
            buckets[index]->length = 0;
        }

        llPushBack(buckets[index], array[i]);
    }

    for (int i = 0; i < bucketsQtd; i++)
        if (buckets[i]) insertionSortLinked(buckets[i]);


    int arrayIndex = 0;

    for (int i = 0; i < bucketsQtd; i++) {
        if (!buckets[i]) continue;

        LinkedListNode* curr = buckets[i]->first;
        while (curr) {
            array[arrayIndex++] = curr->data;
            curr = curr->next;
        }

        llDestroy(buckets[i]);
    }

    free(buckets);
}

void bucketSort(int* array, const int size) {

    const int bucketsQtd = size / 2;

    bucketSortWithBuckets(array, size, bucketsQtd);
}