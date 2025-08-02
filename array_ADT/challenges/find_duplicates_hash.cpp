#include <stdio.h>
#include <stdlib.h>

struct Array
{
    int A[30];
    int size;
    int length;
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

int max(struct Array arr)
{
    int max = arr.A[0];
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i] > max)
            max = arr.A[i];
    }

    return max;
}

// print the element and number of times it appears, if the element appears more than one time in the array. MUST BE SORTED ARRAY
void print_duplicates(struct Array arr)
{
    const int greater_element = arr.A[arr.length - 1];
    int bitmap[greater_element] = {0};

    for (int i = 0; i < arr.length; i++)
    {
        bitmap[arr.A[i]]++;
    }

    for (int i = arr.A[0]; i < greater_element; i++)
    {
        if (bitmap[i] > 1)
            printf("Element '%d' has %d copys in the array\n", i, bitmap[i]);
    }
} // time complexity: O(n)

int main()
{
    struct Array arr = {{3, 6, 8, 8, 10, 12, 15, 15, 15, 20}, 15, 10};

    print_duplicates(arr);
    display(arr);

    return 0;
}