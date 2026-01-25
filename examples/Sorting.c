#include "Algorithms/Sorting.h"
#include "Core/Array/Array.h"

#include <stdio.h>

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    insertionSortArray(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}