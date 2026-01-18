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

// combines two sorted arrays
struct Array* merge(struct Array *arr1, struct Array *arr2)
{
    int i=0, j=0, k=0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while (i < arr1->length && j < arr2->length)
    {
        if(arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];
        else
            arr3->A[k++] = arr2->A[j++];
    }

    for (; i < arr1->length;i++)
        arr3->A[k++] = arr1->A[i];

    for (; j < arr2->length; j++)
        arr3->A[k++] = arr2->A[j];

    arr3->length = arr1->length + arr2->length;
    arr3->size = 10; // setting default value

    return arr3;
} // time complexity: θ(m+n) or just θ(n)

    int main()
{
    struct Array arr1 = {{2, 4, 6, 8, 10}, 10, 5};
    struct Array arr2 = {{1, 3, 7, 9, 12}, 10, 5};
    struct Array *arr3;

    arr3 = merge(&arr1, &arr2);
    display(*arr3);

    return 0;
}