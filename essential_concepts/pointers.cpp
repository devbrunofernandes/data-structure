#include <iostream>
#include <stdlib.h>

using namespace std;
/*
pointers are used for:
access Heap memory.
access resources external to the program.
parameter passing.
*/

int main() {
    int number = 10; // declaration of a data variable and inicialization with 10 value.
    int *pointer; // declaration of a address variable or a pointer.
    pointer = &number; // passing the address of "number" as value to "pointer", '&' is the sign for reference or the address of a variable.

    printf("Get variable value with pointer:%d\n", *pointer); // here '*' is used for dereferenciation, it means get the value that is in that address of the pointer.

    int A[] = {2, 4, 6, 8, 10};
    int *arrayPointer;
    arrayPointer = A;

    printf("Loop printing array values using pointer:\n");
    for (int i = 0; i < 5; i++) {
        cout << arrayPointer[i] << endl;
    }

    int *arrayHeap;
    int *arrayHeapCpp;

    arrayHeap = (int *)malloc(5 * sizeof(int)); // ask for malloc allocate 5 integers in memory and the pointer points to the address of this sequence of bytes.
    arrayHeapCpp = new int[5]; // same using C++ syntax.
    arrayHeap[0] = 10;
    arrayHeap[1] = 15;
    arrayHeap[2] = 20;
    arrayHeap[3] = 25;
    arrayHeap[4] = 30;

    arrayHeapCpp[0] = 12;
    arrayHeapCpp[1] = 34;
    arrayHeapCpp[2] = 56;
    arrayHeapCpp[3] = 78;
    arrayHeapCpp[4] = 910;

    printf("Printing array created in heap with malloc:\n");
    for (int i = 0; i < 5; i++)
    {
        cout << arrayHeap[i] << endl;
    }

    printf("Printing array created in heap with 'new' (C++ syntax):\n");
    for (int i = 0; i < 5; i++)
    {
        cout << arrayHeapCpp[i] << endl;
    }

    free(arrayHeap); // free the memory after using it.
    delete[] arrayHeapCpp; // same with C++ syntax.

    return 0;
}