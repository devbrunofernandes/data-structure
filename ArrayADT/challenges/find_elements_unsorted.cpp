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

int min(struct Array arr)
{
    int min = arr.A[0];
    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i] < min)
            min = arr.A[i];
    }

    return min;
}

// unsorted array with MULTIPLE missing element
struct Array find_multi_missing(struct Array arr)
{
    const int max_element = max(arr), min_element = min(arr);
    struct Array missing_elements = {{}, arr.size, 0};
    bool check_array[max_element] = {0};
    int index = 0;

    for (int i = 0; i < arr.length; i++)
    {
        check_array[arr.A[i]] = 1;
    }

    for (int i = min_element; i <= max_element; i++)
    {
        if (check_array[i] == 0)
        {
            missing_elements.A[index] = i;
            index++;
            missing_elements.length++;
        }
    }

    return missing_elements;
} // time complexity: O(n)

int main()
{
    struct Array arr = {{3, 7, 4, 9, 12, 6, 1, 11, 2, 10}, 15, 10};

    printf("missing element: \n");
    display(find_multi_missing(arr));
    display(arr);

    return 0;
}