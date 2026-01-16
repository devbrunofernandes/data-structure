/*
    Time complexity: O(n log n)
    Space complexity: O(1) - dont use extra space.
    Is NOT Adaptive - can NOT check if array is already sorted and stop the sorting.
    Is NOT Stable - can NOT keep the current order of same weight elements.

    Can be used to sort only a section of list - with 3 passes the list will have 3 greater elements in the end.

    This implemetantion use functions from C++ STL. To see heap implementation go to /heap/ directory in this project.
*/

#include <stdio.h>
#include <algorithm>

void printArray(int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

void heapSort(int* array, const int size) {

    std::make_heap(&array[0], &array[size]);

    for (int i = 0; i < size; i++)
        std::pop_heap(&array[0], &array[size - i]);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    heapSort(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}