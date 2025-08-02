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

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// default linear search.
/*

    int linear_search(struct Array arr, int key)
    {
        for (int i = 0; i < arr.length;i++)
        {
            if(key==arr.A[i])
                return i;
        }
        return -1;
    }

*/
// transposition method of optimization.
/* every time a search is successful the algorithm swaps the element with its previous element in array.

    int linear_search(struct Array *arr, int key)
    {
        for (int i = 0; i < arr->length; i++)
        {
            if (key == arr->A[i])
            {
                if (i!=0)
                {
                    swap(&arr->A[i], &arr->A[i - 1]);
                    return i - 1;
                }
                else
                {
                    return i;
                }
            }
        }
        return -1;
    }

*/
// move to first/header method of optimization.
/* every time a search is successful the algorithm swaps the element with the first element of the array.

    int linear_search(struct Array *arr, int key)
    {
        for (int i = 0; i < arr->length; i++)
        {
            if (key == arr->A[i])
            {
                if (i!=0)
                {
                    swap(&arr->A[i], &arr->A[0]);
                    return 0;
                }
                else
                {
                    return i;
                }
            }
        }
        return -1;
    }

*/
// linear search time complexity O(n).
int linear_search(struct Array *arr, int key)
{
    for (int i = 0; i < arr->length; i++)
    {
        if (key == arr->A[i])
        {
            if (i!=0)
            {
                swap(&arr->A[i], &arr->A[0]);
                return 0;
            }
            else
            {
                return i;
            } 
        }
    }
    return -1;
}

int main()
{
    struct Array arr = {{2, 4, 6, 8, 10}, 10, 5};

    int key = 2;
    printf("index of element %d: [%d]\n", key, linear_search(&arr, key));
    display(arr);

    return 0;
}