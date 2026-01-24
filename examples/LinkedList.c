#include "Core/LinkedLists/CircularLinkedList.h"
#include "Core/LinkedLists/DoublyCircularLinkedList.h"
#include "Core/LinkedLists/LinkedList.h"
#include "Core/LinkedLists/DoublyLinkedList.h"

int main() {

    int A[] = {10,20,30,40,50};
    LinkedList* ll = arrayToLinkedList(A, 5);

    llInsert(ll, 2, 25);

    llDisplay(ll);

    return 0;
}