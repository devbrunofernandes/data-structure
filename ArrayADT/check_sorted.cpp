#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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

// check if array is sorted and return boolean data
bool is_sorted(struct Array arr)
{
    for (int i = 0; i < arr.length-1; i++)
    {
        if (arr.A[i] > arr.A[i+1])
            return false;
    }

    return true;
} // time complexity O(n)

int main()
{
    struct Array arr = {{4, 8, 13, 16, 20, 25, 28, 33}, 10, 8};

    printf("is array sorted?\n");
    std::cout << is_sorted(arr) << std::endl;
    display(arr);

    return 0;
}