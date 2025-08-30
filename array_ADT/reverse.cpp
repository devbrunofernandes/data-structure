#include <stdio.h>
#include <stdlib.h>

// representing a abstract data type of array in C syntax.
struct Array
{
    int A[10];  // pointer to array element.
    int size;   // full size of the array.
    int length; // used space in array.
};

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

// this function reverses the position of elements in array.
// first method. using auxiliar array.
void reverse1(struct Array *arr)
{
    struct Array aux;

    for (int i = arr->length-1, j = 0; i >= 0; i--, j++)
    {
        aux.A[j] = arr->A[i];
    }

    for (int i = 0; i < arr->length; i++)
    {
        arr->A[i] = aux.A[i];
    }
} // time complexity: O(n)

// second method. using swap of elements.
void reverse2(struct Array *arr)
{
    for (int i = arr->length - 1, j = 0; i > j; i--, j++)
    {
        swap(&arr->A[i], &arr->A[j]);
    }
} // time complexity: O(n)

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    reverse2(&arr);
    display(arr);

    return 0;
}