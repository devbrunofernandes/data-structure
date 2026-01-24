/*
    Time complexity: O(n + k) - k is the range between min and max value in list.
    Space complexity: O(n + k) - high memory use.
    Is NOT Adaptive - can NOT easily sort an almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Didactic implementation. Inefficient for integers (use Count Sort).
    Its non-comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>
#include "Core/LinkedLists/LinkedList.h"
#include "Core/Array.h"
#include "Algorithms/Sorting.h"

void binSort(int* array, const int size) {

    const MinMax mm = findMinMax(array, size);

    const int min = mm.min;
    const int max = mm.max;

    const int range = max - min + 1;

    LinkedListNode** bins = (LinkedListNode**) calloc((max - min) + 1, sizeof(LinkedListNode*));

    for (int i = 0; i < size; i++) {

        LinkedListNode* bin = bins[array[i] - min];

        LinkedListNode* newNode = (LinkedListNode*) malloc(sizeof(LinkedListNode));
        newNode->data = array[i];
        newNode->next = NULL;

        while (bin && bin->next) bin = bin->next;

        if (!bin)
            bins[array[i] - min] = newNode;
        else
            bin->next = newNode;
    }
    
    int index = 0;

    for (int i = 0; i < range; i++) {

        while (bins[i]) {
            LinkedListNode* bin = bins[i];
            
            array[index++] = bin->data;

            bins[i] = bin->next;

            free(bin);
        }
    }
    free(bins);
}