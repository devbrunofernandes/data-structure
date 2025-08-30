#include <stdio.h>
#include <stdlib.h>

struct Array
{
    int A[10];
    int size;
    int length;
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

// sorted array with ONE missing element in order
int find_missing(struct Array arr)
{
    int first_element = arr.A[0];

    for (int i = 0; i < arr.length; i++)
    {
        if(arr.A[i] - i != first_element)
            return first_element + i;
    }

    return 0;
} // time complexity: O(n)

int main()
{
    struct Array arr = {{1, 2, 3, 4, 5, 6, 8, 9, 10, 11}, 15, 10};

    printf("missing element: %d\n", find_missing(arr));
    display(arr);

    return 0;
}