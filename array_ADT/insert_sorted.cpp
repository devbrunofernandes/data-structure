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

// in sorted arrays, insert in the right position.
void insert_sorted(struct Array *arr, int x)
{
    if (arr->length == arr->size)
        return;

    int i = arr->length - 1;
    while (i >= 0 && arr->A[i] > x)
    {
        arr->A[i + 1] = arr->A[i];
        i--;
    }
    arr->A[i+1] = x;
    arr->length++;
} // time complexity O(n)

int main()
{
    struct Array arr = {{4, 8, 13, 16, 20, 25, 28, 33}, 10, 8};

    insert_sorted(&arr, 22);
    display(arr);

    return 0;
}