/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sorted only needs one comparation for each element.
    Is Stable - keeps the current order of same weight elements.

    Is more friendly with Linked Lists because of insertion behavior.
    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property. 
*/

#include <stdio.h>
#include "Algorithms/Sorting.h"

void insertInSortedPositionLinked(LinkedList* ll, LinkedListNode* key) {
    
    LinkedListNode* p = ll->first;
    LinkedListNode* tail = NULL;

    while (p && key->data >= p->data) {
        tail = p;
        p = p->next;
    }

    if (tail) tail->next = key;
    else ll->first = key;

    if (!p) ll->last = key;
    key->next = p;
}

void insertionSortLinked(LinkedList* ll) {

    if (ll->length < 2) return;

    LinkedListNode* p = ll->first->next->next;
    LinkedListNode* tail = ll->first->next;

    ll->first->next = NULL;
    ll->last = ll->first;

    for (int i = 1; i < ll->length; i++) {
        
        insertInSortedPositionLinked(ll, tail);
        tail = p;
        if (p) p = p->next;
    }
}