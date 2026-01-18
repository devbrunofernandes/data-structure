/*
    Time complexity: O(n^2)
    Space complexity: O(1) - dont use extra space.
    Is NOT Adaptive - can NOT easily sort a almost sorted list or stop if list became sorted in the middle of processing. Always O(n^2)
    Is NOT Stable - Can NOT keep the current order of same weight elements.

    Can be used to sort only a section of list - with 3 passes the list will have 3 smallest elements in the beginning.
    Can be used for minimum write in memory - only writes the element in his final place of the list. O(n) writes in memory.
*/

#include <stdio.h>

void printArray(int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

void pass(int* array, const int size, const int index) {

    int minor = index;

    for (int i = index + 1; i < size; i++) {
        if (array[i] < array[minor]) minor = i;
    }

    int temp = array[index];
    array[index] = array[minor];
    array[minor] = temp;
}

void selectionSort(int* array, const int size) {

    for (int i = 0; i < size - 1; i++)
        pass(array, size, i);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    selectionSort(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}