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
    int element;
    int index = 0;

    for (int i = 0; i < arr.length-1; i++)
    {
        if (arr.A[i] == arr.A[i+1])
        {
            element = arr.A[i];
            duplicate_elements.A[index] = element;
            duplicate_elements.length++;
            index++;

            while (arr.A[i] == element && i < arr.length - 1)
                i++;
        }
    }

    return duplicate_elements;
} // time complexity: O(n)

// return the number of elements that appears more than one time in array
int count_duplicates(struct Array arr)
{
    int element, total_duplicates = 0;

    for (int i = 0; i < arr.length - 1; i++)
    {
        if (arr.A[i] == arr.A[i + 1])
        {
            element = arr.A[i];
            total_duplicates++;

            while (arr.A[i] == element && i < arr.length-1)
                i++;
        }
    }

    return total_duplicates;
}

// print the element and number of times it appears, if the element appears more than one time in the array.
void print_duplicates(struct Array arr)
{
    int element;
    int j;

    for (int i = 0; i < arr.length - 1; i++)
    {
        if (arr.A[i] == arr.A[i + 1])
        {
            element = arr.A[i];
            j = i;
            while (arr.A[j] == element && j < arr.length)
                j++;
            printf("element '%d': appears %d times\n", element, j-i);
            i = j;
        }
    }
}

int main()
{
    struct Array arr = {{3, 6, 8, 8, 10, 12, 15, 15, 15, 20}, 15, 10};

    printf("duplicate element: \n");
    display(find_duplicates(arr));
    printf("Total of duplicates: %d\n", count_duplicates(arr));
    print_duplicates(arr);
    display(arr);

    return 0;
}