#include <iostream>
#include <stdlib.h>

using namespace std;

struct Rectangle {
    int length;
    int breadth;
};

int main() {
    struct Rectangle r = {10, 5};
    struct Rectangle *pointer = &r;

    pointer->length = 20; // use this arrow syntax to access an pointer address and one of its variables.
    printf("Rectangle r length: %d\n", pointer->length);

    (*pointer).length = 30; // syntax for equivalent result but worst to read.
    printf("Rectangle r length: %d\n", pointer->length);


    struct Rectangle *structInHeap = (struct Rectangle *)malloc(sizeof(struct Rectangle)); // declaration of struct type in heap.
    // Rectangle *structInHeap = new Rectangle; --> this is C++ much better exclusive syntax for the same line above.
    structInHeap->length = 40;
    structInHeap->breadth = 20;
    printf("Rectangle structInHeap length: %d\n", structInHeap->length);

    free(structInHeap);
    return 0;
}