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

// creates and return a list of duplicate elements of an array. MUST BE SORTED version.
struct Array find_duplicates(struct Array arr)
{
    struct Array duplicate_elements = {{}, arr.size, 0};
    const int greater_element = max(arr);
    int bitmap[greater_element + 1] = {0};
    int index = 0;

    for (int i = 0; i < arr.length; i++)
    {
        bitmap[arr.A[i]]++;
    }

    for (int i = 0; i <= greater_element; i++)
    {
        if (bitmap[i] > 1)
        {
            duplicate_elements.A[index] = i;
            index++;
            duplicate_elements.length++;
        }
    }

    return duplicate_elements;
} // time complexity: O(n)

// return the number of elements that appears more than one time in array
int count_duplicates(struct Array arr)
{
    int total_duplicates = 0;
    const int greater_element = max(arr);
    int bitmap[greater_element + 1] = {0};

    for (int i = 0; i < arr.length; i++)
    {
        bitmap[arr.A[i]]++;
    }

    for (int i = 0; i <= greater_element; i++)
    {
        if (bitmap[i] > 1)
        {
            total_duplicates++;
        }
    }

    return total_duplicates;
} // time complexity: O(n)

// print the element and number of times it appears, if the element appears more than one time in the array.
void print_duplicates(struct Array arr)
{
    const int greater_element = max(arr);
    int bitmap[greater_element + 1] = {0};

    for (int i = 0; i < arr.length; i++)
    {
        bitmap[arr.A[i]]++;
    }

    for (int i = 0; i <= greater_element; i++)
    {
        if (bitmap[i] > 1)
        {
            printf("element '%d': appears %d times\n", i, bitmap[i]);
        }
    }
} // time complexity: O(n)

int main()
{
    struct Array arr = {{8, 3, 6, 4, 6, 5, 6, 8, 2, 7}, 15, 10};

    printf("duplicate element: \n");
    display(find_duplicates(arr));
    printf("Total of duplicates: %d\n", count_duplicates(arr));
    print_duplicates(arr);
    display(arr);

    return 0;
}