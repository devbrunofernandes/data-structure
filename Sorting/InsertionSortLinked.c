/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is Adaptive - if array is already sorted only needs one comparation for each element.
    Is Stable - keeps the current order of same weight elements.

    Is more friendly with Linked Lists because of insertion behavior.
    Is "online algorithm" by nature - can quickly insert a new element in a sorted list keeping the sorting property. 
*/

#include <stdio.h>
#include "headers/InsertionSortLinked.h"

void insertInSortedPosition(LinkedList* ll, Node* key) {
    
    Node* p = ll->first;
    Node* tail = NULL;

    while (p && key->data >= p->data) {
        tail = p;
        p = p->next;
    }

    if (tail) tail->next = key;
    else ll->first = key;

    if (!p) ll->last = key;
    key->next = p;
}

void insertionSort(LinkedList* ll) {

    if (ll->length < 2) return;

    Node* p = ll->first->next->next;
    Node* tail = ll->first->next;

    ll->first->next = NULL;
    ll->last = ll->first;

    for (int i = 1; i < ll->length; i++) {
        
        insertInSortedPosition(ll, tail);
        tail = p;
        if (p) p = p->next;
    }
}

// int main() {
//     const int size = 11;
//     int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};
//
//     LinkedList* ll = arrayToLinkedList(array, size);
//
//     printf("Array before sort: ");
//     print(ll);
//
//     insertionSort(ll);
//
//     printf("Array after sort: ");
//     print(ll);
//
//     return 0;
// }