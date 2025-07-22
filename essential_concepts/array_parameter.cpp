#include <iostream>

using namespace std;

void arrayPrint(int A[], int size);
int *createArray(int size);

int main()
{
    int array[5] = {2, 4, 6, 8, 10};

    arrayPrint(array, 5);

    int *arrayPointer;
    arrayPointer = createArray(5);
    arrayPointer[0] = 10;
    printf("%d\n", arrayPointer[0]);

    return 0;
}

// function receiving array as parameter.
// pass as parameters the array itself and the size of the array.
void arrayPrint(int A[], int size) // the parameter empty array will be a pointer to array from where it has been called. parameter A[] passed by address.
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

// function returning array.
int *createArray(int size) // return value is a pointer.
{
    int *p;
    p = (int *)malloc(size * sizeof(int)); // create the array in heap memory inside the function.
    return (p); // return the pointer to the created array.
}