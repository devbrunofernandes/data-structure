#ifndef INSERTION_SORT_LINKED
#define INSERTION_SORT_LINKED

/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sorted only needs one comparation for each element.
    Is Stable - keeps the current order of same weight elements.

    Is more friendly with Linked Lists because of insertion behavior.
    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property. 
*/

#include "../../LinkedLists/SinglyLinkedList/LinkedList.h"

void insertInSortedPosition(LinkedList* ll, Node* key);

void insertionSort(LinkedList* ll);

#endif