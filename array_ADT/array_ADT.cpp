#include <stdio.h>
#include <stdlib.h>

// representing a abstract data type of array in C syntax
struct Array
{
    int *A;     // pointer to array element
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
    struct Array arr;
    printf("Enter size of array: ");
    scanf("%d", &arr.size);

    arr.A = (int *)malloc(arr.size * sizeof(int));
    arr.length = 0;

    int n;
    printf("Enter number of numbers: ");
    scanf("%d", &n);

    printf("Enter all elements:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr.A[i]);
    arr.length = n;

    display(arr);

    return 0;
}