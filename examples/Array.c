#include "Core/Array.h"

#include <stdio.h>

#define MAX_SIZE 20

int main() {
    int array[MAX_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int currSize = 10;

    printf("Sum of array: %d\n", sumArray(array, currSize));

    return 0;
}