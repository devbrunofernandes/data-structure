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

void insert(struct Array *arr, int index, int x)
{
    // this version of insert only inserts if have avaliable space in array. it don't resize the array!
    // checking if index is valid. greater than 0 and less or equal to array length.
    if(index>=0 && index <= arr->length)
    {
        for (int i = arr->length; i > index; i--)
            arr->A[i] = arr->A[i - 1];
        arr->A[index] = x;
        arr->length++;
    }
}

void append(struct Array *arr, int x)
{
    // this version of append only works if there is avaliable space in array. it don't resize the array!
    // checking if have space in array to appending.
    if (arr->length < arr->size)
    {
        arr->A[arr->length++] = x;
    }
}

int main()
{
    struct Array arr = {{2, 3, 4, 5, 6}, 10, 5};

    insert(&arr, 2, 10);
    display(arr);

    return 0;
}
