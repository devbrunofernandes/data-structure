#include <stdio.h>
#include <stdlib.h>

// representing a abstract data type of array in C syntax.
struct Array
{
    int A[10];  // pointer to array element.
    int size;   // full size of the array.
    int length; // used space in array.
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

// get a element of given index
int get(struct Array arr, int index)
{
    if (index >= 0 && index < arr.length)
        return arr.A[index];

    return NULL;
} // time complexity: O(1)

// set a element of given index to other value
void set(struct Array *arr, int index, int value)
{
    if (index >= 0 && index < arr->length)
        arr->A[index] = value;
} // time complexity: O(1)

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    int index = 0;
    printf("element of index [%d]: %d\n", index, get(arr, index));
    set(&arr, index, 0);
    display(arr);

    return 0;
}