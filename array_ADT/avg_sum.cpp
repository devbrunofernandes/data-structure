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

// get the sum of array values
int sum(struct Array arr)
{
    int total = 0;
    for (int i = 0; i < arr.length; i++)
    {
        total += arr.A[i];
    }

    return total;
} // time complexity: O(n)

// get the sum of array values
float avg(struct Array arr)
{
    return (float) sum(arr)/arr.length;
} // time complexity: O(n)

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    printf("sum: %d\n", sum(arr));
    printf("avg: %f\n", avg(arr));

    display(arr);

    return 0;
}