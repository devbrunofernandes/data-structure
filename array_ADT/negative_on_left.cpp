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

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// separate negative numbers from positive numbers in array.
void rearrange(struct Array *arr)
{
    int i=0, j=arr->length-1;

    while (i < j)
    {
        while(arr->A[i] < 0)
            i++;

        while(arr->A[j] >= 0)
            j--;

        if (i<j)
            swap(&arr->A[i], &arr->A[j]);
    }
} // time complexity O(n)

int main()
{
    struct Array arr = {{2, -3, 10, -1, 20, -25, -7, 33}, 10, 8};

    rearrange(&arr);
    display(arr);

    return 0;
}