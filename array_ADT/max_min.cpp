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

// get the maximum value in array
int max(struct Array arr)
{
    int max = arr.A[0];
    for (int i = 0; i < arr.length;i++)
    {
        if (arr.A[i] > max)
            max = arr.A[i];
    }

    return max;
} // time complexity: O(n)

// get the minimum value in array
int min(struct Array arr)
{
    int min = arr.A[0];
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i] < min)
            min = arr.A[i];
    }

    return min;
} // time complexity: O(n)

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    printf("max: %d\n", max(arr));
    printf("min: %d\n", min(arr));

    display(arr);

    return 0;
}