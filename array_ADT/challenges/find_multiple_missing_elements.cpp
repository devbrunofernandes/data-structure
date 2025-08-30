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

// sorted array with MULTIPLE missing element
struct Array find_multi_missing(struct Array arr)
{
    struct Array missing_elements = {{}, arr.size, 0};
    int index = 0;
    int first_element = arr.A[0];
    int diff = first_element;

    for (int i = 0; i < arr.length; i++)
    {
        if (arr.A[i] - i != diff)
            while (arr.A[i] - i > diff)
            {
                missing_elements.A[index++] = diff + i;
                diff++;
                missing_elements.length++;
            }
    }

    return missing_elements;
}

int main()
{
    struct Array arr = {{6, 7, 8, 9, 11, 12, 15, 16, 17, 18, 19}, 15, 11};

    printf("missing element: \n");
    display(find_multi_missing(arr));
    display(arr);

    return 0;
}