#include "LinkedList.h"

int main() {

    int A[] = {10,20,30,40,50};
    LinkedList* ll = arrayToLinkedList(A, 5);

    insert(ll, 2, 25);

    printf("length is %d\n", ll->length);
    print(ll);

    return 0;
}