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

// move all elements to the left
void left_rotate(struct Array *arr)
{
    int first_element = arr->A[0];

    for (int i = 0; i < arr->length - 1; i++)
    {
        arr->A[i] = arr->A[i + 1];
    }

    arr->A[arr->length - 1] = first_element;
    // arr->length--;
}

// move all elements to the right
void right_rotate(struct Array *arr)
{
    int last_element = arr->A[arr->length - 1];

    for (int i = arr->length - 1; i >= 0; i--)
    {
        arr->A[i] = arr->A[i - 1];
    }

    arr->A[0] = last_element;
    // arr->length--;
}

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    right_rotate(&arr);
    right_rotate(&arr);
    display(arr);

    return 0;
}