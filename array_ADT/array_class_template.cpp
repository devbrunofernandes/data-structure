#include <stdio.h>
#include <stdlib.h>

template <class T>
class Array
{
private:
    T *A;
    int size;
    int length;
    void swap(int *x, int *y);

public:
    Array()
    {
        size = 10;
        length = 0;
        A = new T[size];
    }

    Array(int sz)
    {
        size = sz;
        length = 0;
        A = new T[size];
    }

    ~Array()
    {
        delete[] A;
    }

    void display();
    void insert(int index, T x);
    void append(T x);
    T erase(int index);
    int linear_search(T key);
    int binary_search(T key);
    T get(int index);
    void set(int index, T value);
    T max();
    T min();
    T sum();
    float avg();
    void reverse1();
    void reverse2();
    void insert_sorted(T x);
    bool is_sorted();
    void rearrange();
    Array *merge(Array arr2);
    Array *set_union(Array arr2);
    Array *set_intersection(Array arr2);
    Array *set_difference(Array arr2);
};

template <class T>
void Array<T>::display()
{
    for (int i = 0; i < length; i++)
        printf("%d ", A[i]);
    printf("\n");
}

template <class T>
void Array<T>::insert(int index, T x)
{
    if (index >= 0 && index <= length)
    {
        for (int i = length; i > index; i--)
            A[i] = A[i - 1];
        A[index] = x;
        length++;
    }
}

template <class T>
void Array<T>::append(T x)
{
    if (length < size)
    {
        A[length++] = x;
    }
}

template <class T>
T Array<T>::erase(int index)
{
    T x = 0;

    if (index >= 0 && index < length)
    {
        x = A[index];

        for (int i = index; i < length - 1; i++)
            A[i] = A[i + 1];
        length--;
        A[length] = 0;
    }

    return x;
}

template <class T>
void Array<T>::swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

template <class T>
int Array<T>::linear_search(T key)
{
    for (int i = 0; i < length; i++)
    {
        if (key == A[i])
        {
            if (i != 0)
            {
                swap(&A[i], &A[0]);
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

template <class T>
int Array<T>::binary_search(T key)
{
    int l, mid, h;
    l = 0;
    h = length - 1;

    while (l <= h)
    {
        mid = (h + l) / 2;

        if (key == A[mid])
            return mid;
        else if (key < A[mid])
            h = mid - 1;
        else
            l = mid + 1;
    }

    return -1;
}

template <class T>
T Array<T>::get(int index)
{
    if (index >= 0 && index < length)
        return A[index];

    return -1;
}

template <class T>
void Array<T>::set(int index, T value)
{
    if (index >= 0 && index < length)
        A[index] = value;
}

template <class T>
T Array<T>::max()
{
    T max = A[0];
    for (int i = 0; i < length; i++)
    {
        if (A[i] > max)
            max = A[i];
    }

    return max;
}

template <class T>
T Array<T>::min()
{
    T min = A[0];
    for (int i = 0; i < length; i++)
    {
        if (A[i] < min)
            min = A[i];
    }

    return min;
}

template <class T>
T Array<T>::sum()
{
    T total = 0;
    for (int i = 0; i < length; i++)
    {
        total += A[i];
    }

    return total;
}

template <class T>
float Array<T>::avg()
{
    return (float)sum() / length;
}

template <class T>
void Array<T>::reverse1()
{
    Array aux;

    for (int i = length - 1, j = 0; i >= 0; i--, j++)
    {
        aux.A[j] = A[i];
    }

    for (int i = 0; i < length; i++)
    {
        A[i] = aux.get(i);
    }
}

template <class T>
void Array<T>::reverse2()
{
    for (int i = length - 1, j = 0; i > j; i--, j++)
    {
        swap(&A[i], &A[j]);
    }
}

template <class T>
void Array<T>::insert_sorted(T x)
{
    if (length == size)
        return;

    int i = length - 1;
    while (i >= 0 && A[i] > x)
    {
        A[i + 1] = A[i];
        i--;
    }
    A[i + 1] = x;
    length++;
}

template <class T>
bool Array<T>::is_sorted()
{
    for (int i = 0; i < length - 1; i++)
    {
        if (A[i] > A[i + 1])
            return false;
    }

    return true;
}

template <class T>
void Array<T>::rearrange()
{
    int i = 0, j = length - 1;

    while (i < j)
    {
        while (A[i] < 0)
            i++;

        while (A[j] >= 0)
            j--;

        if (i < j)
            swap(&A[i], &A[j]);
    }
}

template <class T>
Array<T> *Array<T>::merge(Array<T> arr2)
{
    int i = 0, j = 0, k = 0;
    Array<T> *arr3 = new Array(length + arr2.length);

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
            arr3->A[k++] = A[i++];
        else
            arr3->A[k++] = arr2.A[j++];
    }

    for (; i < length; i++)
        arr3->A[k++] = A[i];

    for (; j < arr2.length; j++)
        arr3->A[k++] = arr2.A[j];

    arr3->length = length + arr2.length;

    return arr3;
}

template <class T>
Array<T> *Array<T>::set_union(Array<T> arr2)
{
    int i = 0, j = 0, k = 0;
    Array<T> *arr3 = new Array(length + arr2.length);

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
        {
            arr3->A[k++] = A[i++];
        }
        else if (arr2.A[j] < A[i])
        {
            arr3->A[k++] = arr2.A[j++];
        }
        else
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }

    for (; i < length; i++)
        arr3->A[k++] = A[i];

    for (; j < arr2.length; j++)
        arr3->A[k++] = arr2.A[j];

    arr3->length = length + arr2.length;

    return arr3;
}

template <class T>
Array<T> *Array<T>::set_intersection(Array<T> arr2)
{
    int i = 0, j = 0, k = 0;
    Array<T> *arr3 = new Array(length + arr2.length);

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
        {
            i++;
        }
        else if (arr2.A[j] < A[i])
        {
            j++;
        }
        else
        {
            arr3->A[k++] = A[i++];
            j++;
        }
    }

    arr3->length = length + arr2.length;

    return arr3;
}

template <class T>
Array<T> *Array<T>::set_difference(Array<T> arr2)
{
    int i = 0, j = 0, k = 0;
    Array<T> *arr3 = new Array(length + arr2.length);

    while (i < length && j < arr2.length)
    {
        if (A[i] < arr2.A[j])
        {
            arr3->A[k++] = A[i++];
        }
        else if (arr2.A[j] < A[i])
        {
            j++;
        }
        else
        {
            i++;
            j++;
        }
    }

    for (; i < length; i++)
        arr3->A[k++] = A[i];

    arr3->length = length + arr2.length;

    return arr3;
}

int main()
{
    int ch, x, index, sz = 10, array_list_index = 0;
    int selected_array = 0;
    Array<int> array_list[10];
    printf("Enter size of array: ");
    scanf("%d", &sz);

    int arrays = 1;
    Array<int> arr1(sz);
    array_list[array_list_index] = arr1;
    array_list_index++;

    do
    {
        if (arrays == 1)
        {
            printf("\nMenu\n");
            printf("1. Insert\n");
            printf("2. Delete\n");
            printf("3. Search\n");
            printf("4. Sum\n");
            printf("5. Display\n");
            printf("6. Merge\n");
            printf("7. Set operations\n");
            printf("8. Create new array\n");
            printf("9. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &ch);
        }
        else
        {
            printf("Select your array: ");
            scanf("%d", &selected_array);

            printf("\nMenu\n");
            printf("1. Insert\n");
            printf("2. Delete\n");
            printf("3. Search\n");
            printf("4. Sum\n");
            printf("5. Display\n");
            printf("6. Merge\n");
            printf("7. Set operations\n");
            printf("8. Create new array\n");
            printf("9. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &ch);
        }

        switch (ch)
        {
        case 1:
            printf("Enter an element and index: ");
            scanf("%d%d", &x, &index);
            array_list[selected_array].insert(index, x);
            break;
        case 2:
            printf("Enter index: ");
            scanf("%d", &index);
            array_list[selected_array].erase(index);
            break;
        case 3:
            printf("Enter an element to search: ");
            scanf("%d", &x);
            index = array_list[selected_array].linear_search(x);
            printf("Element index: %d\n", index);
            break;
        case 4:
            printf("Sum is: %d\n", array_list[selected_array].sum());
            break;
        case 5:
            array_list[selected_array].display();
            break;
        case 6:
        {
            printf("Enter array number to merge with: ");
            scanf("%d", &x);
            Array<int> *new_array = array_list[selected_array].merge(array_list[x]);
            array_list[array_list_index] = *new_array;
            array_list_index++;
            arrays++;
            break;
        }
        case 7:
            array_list[selected_array].display();
            break;
        case 8:
        {
            Array<int> new_arr(sz);
            array_list[array_list_index] = new_arr;
            array_list_index++;
            arrays++;
            break;
        }
        }
    } while (ch != 9);

    return 0;
}