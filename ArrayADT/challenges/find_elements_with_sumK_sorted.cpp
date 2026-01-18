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

// find and print a couple of numbers in an array that sums is equal to parameter 'sum'. works in SORTED arrays
void elements_for_sum(struct Array arr, int sum)
{
    // this algorithm no handle with duplicates, if you need use this with duplicate elements call remove duplicates function first
    int i=0, j=arr.length-1;
    bool found_sum = false;

    while (i<j)
    {
        if (arr.A[i] + arr.A[j] == sum)
        {
            found_sum = true;
            printf("Sum %d + %d = %d\n", arr.A[i], arr.A[j], sum);
            i++;
            j--;
        }
        else if (arr.A[i] + arr.A[j] < sum)
        {
            i++;
        }
        else
        {
            j--;
        }
    }

    if (found_sum == false)
    {
        printf("Not found compatible elements that sum is %d\n", sum);
    }
} // time complexity: O(n)

int main()
{
    struct Array arr = {{6, 3, 8, 10, 16, 7, 5, 2, 9, 14}, 15, 10};

    elements_for_sum(arr, 20);
    display(arr);

    return 0;
}