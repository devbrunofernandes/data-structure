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

// SET OPERATIONS ===============================================================================================================================
// this operations are only for sorted arrays/sets, algorithms of this operations without using sorted can be done also but they are slow O(n**2)
// performs union operation in sets - merge two sets/arrays taken just unique values
struct Array *set_union(struct Array *arr1, struct Array *arr2)
{
    int i = 0, j = 0, k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
        {
            arr3->A[k++] = arr1->A[i++];
        }
        else if (arr2->A[j] < arr1->A[i])
        {
            arr3->A[k++] = arr2->A[j++];
        }
        else
        {
            arr3->A[k++] = arr1->A[i++];
            j++;
        }
    }

    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];

    for (; j < arr2->length; j++)
        arr3->A[k++] = arr2->A[j];

    arr3->length = k;
    arr3->size = 10; // setting default value

    return arr3;
} // time complexity: θ(m+n) or just θ(n)

// performs intersection operation in sets - copy for the new set/array only elements that are commom for both sets
struct Array *set_intersection(struct Array *arr1, struct Array *arr2)
{
    int i = 0, j = 0, k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
        {
            i++;
        }
        else if (arr2->A[j] < arr1->A[i])
        {
            j++;
        }
        else
        {
            arr3->A[k++] = arr1->A[i++];
            j++;
        }
    }

    arr3->length = k;
    arr3->size = 10; // setting default value

    return arr3;
} // time complexity: θ(m+n) or just θ(n)

// performs difference operation in sets - copy the values of first set that are not also in the second set
struct Array *set_difference(struct Array *arr1, struct Array *arr2)
{
    int i = 0, j = 0, k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
        {
            arr3->A[k++] = arr1->A[i++];
        }
        else if (arr2->A[j] < arr1->A[i])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];

    arr3->length = k;
    arr3->size = 10; // setting default value

    return arr3;
} // time complexity: θ(m+n) or just θ(n)

int main()
{
    // struct Array set1 = {{2, 6, 10, 15, 25}, 10, 5};
    // struct Array set2 = {{3, 6, 7, 15, 20}, 10, 5};
    struct Array set1 = {{1, 2, 3, 4, 5}, 10, 5};
    struct Array set2 = {{4, 5, 6, 7, 8}, 10, 5};
    struct Array *set3;

    // union
    set3 = set_union(&set1, &set2);
    printf("Union: ");
    display(*set3);

    // intersection
    free(set3);
    set3 = set_intersection(&set1, &set2);
    printf("Intersection: ");
    display(*set3);

    // set1 - set2 difference
    free(set3);
    set3 = set_difference(&set1, &set2);
    printf("set1 - set2 Difference: ");
    display(*set3);

    return 0;
}