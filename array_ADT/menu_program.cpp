#include <stdio.h>
#include <stdlib.h>

// representing a abstract data type of array in C syntax.
struct Array
{
    int *A;
    int size;
    int length;
};

void display(struct Array arr)
{
    for (int i = 0; i < arr.length; i++)
        printf("%d ", arr.A[i]);
    printf("\n");
}

void insert(struct Array *arr, int index, int x)
{
    if (index >= 0 && index <= arr->length)
    {
        for (int i = arr->length; i > index; i--)
            arr->A[i] = arr->A[i - 1];
        arr->A[index] = x;
        arr->length++;
    }
}

void append(struct Array *arr, int x)
{
    if (arr->length < arr->size)
    {
        arr->A[arr->length++] = x;
    }
}

int erase(struct Array *arr, int index)
{
    int x = 0;

    if (index >= 0 && index < arr->length)
    {
        x = arr->A[index];

        for (int i = index; i < arr->length - 1; i++)
            arr->A[i] = arr->A[i + 1];
        arr->length--;
        arr->A[arr->length] = 0;
    }

    return x;
}

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int linear_search(struct Array *arr, int key)
{
    for (int i = 0; i < arr->length; i++)
    {
        if (key == arr->A[i])
        {
            if (i != 0)
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

int binary_search(struct Array arr, int key)
{
    int l, mid, h;
    l = 0;
    h = arr.length - 1;

    while (l <= h)
    {
        mid = (h + l) / 2;

        if (key == arr.A[mid])
            return mid;
        else if (key < arr.A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }

    return -1;
}

int recursive_binary_search(int A[], int l, int h, int key)
{
    if (l <= h)
    {
        int mid = (h + l) / 2;

        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            return recursive_binary_search(A, l, mid - 1, key);
        else
            return recursive_binary_search(A, mid + 1, h, key);
    }

    return -1;
}

int get(struct Array arr, int index)
{
    if (index >= 0 && index < arr.length)
        return arr.A[index];

    return NULL;
}

void set(struct Array *arr, int index, int value)
{
    if (index >= 0 && index < arr->length)
        arr->A[index] = value;
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

int sum(struct Array arr)
{
    int total = 0;
    for (int i = 0; i < arr.length; i++)
    {
        total += arr.A[i];
    }

    return total;
}

float avg(struct Array arr)
{
    return (float)sum(arr) / arr.length;
}

void reverse1(struct Array *arr)
{
    struct Array aux;

    for (int i = arr->length - 1, j = 0; i >= 0; i--, j++)
    {
        aux.A[j] = arr->A[i];
    }

    for (int i = 0; i < arr->length; i++)
    {
        arr->A[i] = aux.A[i];
    }
}

void reverse2(struct Array *arr)
{
    for (int i = arr->length - 1, j = 0; i > j; i--, j++)
    {
        swap(&arr->A[i], &arr->A[j]);
    }
}

void insert_sorted(struct Array *arr, int x)
{
    if (arr->length == arr->size)
        return;

    int i = arr->length - 1;
    while (i >= 0 && arr->A[i] > x)
    {
        arr->A[i + 1] = arr->A[i];
        i--;
    }
    arr->A[i + 1] = x;
    arr->length++;
}

bool is_sorted(struct Array arr)
{
    for (int i = 0; i < arr.length - 1; i++)
    {
        if (arr.A[i] > arr.A[i + 1])
            return false;
    }

    return true;
}

void rearrange(struct Array *arr)
{
    int i = 0, j = arr->length - 1;

    while (i < j)
    {
        while (arr->A[i] < 0)
            i++;

        while (arr->A[j] >= 0)
            j--;

        if (i < j)
            swap(&arr->A[i], &arr->A[j]);
    }
}

struct Array *merge(struct Array *arr1, struct Array *arr2)
{
    int i = 0, j = 0, k = 0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));

    while (i < arr1->length && j < arr2->length)
    {
        if (arr1->A[i] < arr2->A[j])
            arr3->A[k++] = arr1->A[i++];
        else
            arr3->A[k++] = arr2->A[j++];
    }

    for (; i < arr1->length; i++)
        arr3->A[k++] = arr1->A[i];

    for (; j < arr2->length; j++)
        arr3->A[k++] = arr2->A[j];

    arr3->length = arr1->length + arr2->length;
    arr3->size = 10;

    return arr3;
}

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
    arr3->size = 10;

    return arr3;
}

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
    arr3->size = 10;

    return arr3;
}

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
    arr3->size = 10;

    return arr3;
}

int main()
{
    int ch, x, index;

    struct Array arr1;
    printf("Enter size of array: ");
    scanf("%d", &arr1.size);

    arr1.A = (int *)malloc(arr1.size * sizeof(int));
    arr1.length = 0;

    do
    {
        printf("\nMenu\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Sum\n");
        printf("5. Display\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printf("Enter an element and index: ");
            scanf("%d%d", &x, &index);
            insert(&arr1, index, x);
            break;
        case 2:
            printf("Enter index: ");
            scanf("%d", &index);
            erase(&arr1, index);
            break;
        case 3:
            printf("Enter an element to search: ");
            scanf("%d", &x);
            index=linear_search(&arr1,x);
            printf("Element index: %d\n", index);
            break;
        case 4:
            printf("Sum is: %d\n", sum(arr1));
            break;
        case 5:
            display(arr1);
            break;
        }
    } while (ch < 6);

    return 0;
}