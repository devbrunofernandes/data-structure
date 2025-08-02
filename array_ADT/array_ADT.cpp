#include <stdio.h>
#include <stdlib.h>

// representing a abstract data type of array in C syntax
struct Array
{
    int A[10];  // pointer to array element
    int size;   // full size of the array
    int length; // used space in array
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    display(arr);

    return 0;
}