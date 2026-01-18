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

// find and print a couple of numbers in an array that sums is equal to parameter 'sum'. works in unsorted arrays
void elements_for_sum(struct Array arr, int sum)
{
    // this algorithm no handle with duplicates, if you need use this with duplicate elements call remove duplicates function first
    int need = 0;
    bool found_sum = false;
    for (int i = 0; i < arr.length; i++)
    {
        need = sum - arr.A[i];
        for (int j = i + 1; j < arr.length; j++)
        {
            if (arr.A[j] == need)
            {
                found_sum = true;
                printf("Sum %d + %d = %d\n", arr.A[i], arr.A[j], sum);
            }
        }
    }

    if (found_sum == false)
    {
        printf("Not found compatible elements that sum is %d\n", sum);
    }
} // time complexity: O(n**2)

// same function but faster at price of memory consuming | bitmap/hash stategy
void elements_for_sum2(struct Array arr, int sum)
{
    // this algorithm no handle with duplicates, if you need use this with duplicate elements call remove duplicates function first
    const int greater_element = max(arr);
    int need = 0;
    bool found_sum = false;
    int bitmap[greater_element + 1] = {0};

    for (int i = 0; i < arr.length; i++)
    {
        need = sum - arr.A[i];
        if (need >= 0 && bitmap[need] > 0 && need <= greater_element)
        {
            found_sum = true;
            printf("Sum %d + %d = %d\n", arr.A[i], need, sum);
        }
        bitmap[arr.A[i]]++;
    }

    if (found_sum == false)
    {
        printf("Not found compatible elements that sum is %d\n", sum);
    }
} // time complexity: O(n)

int main()
{
    struct Array arr = {{6, 3, 8, 10, 16, 7, 5, 2, 9, 14}, 15, 10};

    elements_for_sum2(arr, 20);
    display(arr);

    return 0;
}