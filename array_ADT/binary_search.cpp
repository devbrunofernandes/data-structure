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

// iterative binary search algorithm - all elements in array MUST be sorted.
int binary_search(struct Array arr, int key)
{
    int l, mid, h;
    l = 0;
    h = arr.length - 1;

    while (l <= h)
    {
        mid = (h + l) / 2;

        if (key == arr.A[mid])
            return mid;
        else if (key < arr.A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }

    return -1;
} // binary search time complexity O(log n).

// recursive binary search algorithm - all elements in array MUST be sorted.
int recursive_binary_search(int A[], int l, int h, int key)
{
    if (l <= h)
    {
        int mid = (h + l) / 2;

        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            return recursive_binary_search(A, l, mid - 1, key);
        else
            return recursive_binary_search(A, mid + 1, h, key);
    }

    return -1;
} // binary search time complexity O(log n).

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    int key = 2;
    printf("index of element %d: [%d]\n", key, recursive_binary_search(arr.A, 0, arr.length, key));
    display(arr);

    return 0;
}