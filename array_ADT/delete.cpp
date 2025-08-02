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

// erase or delete function of a element in array.
int erase(struct Array *arr, int index)
{
    int x = 0;

    if(index>=0 && index < arr->length)
    {
        x = arr->A[index];

        for (int i = index; i < arr->length - 1;i++)
            arr->A[i] = arr->A[i + 1];
        arr->length--;
        arr->A[arr->length] = 0;
    }

    return x;
}

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    printf("%d\n", erase(&arr, 2));
    display(arr);

    return 0;
}