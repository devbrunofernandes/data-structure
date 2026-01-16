/*
    Time complexity: O(n + k) - k is the greater value in list
    Space complexity: O(n + k) - high memory use.
    Is NOT Adaptive - can NOT easily sort a almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Only indicated for lists with short range of possible numbers. Otherwise can use really high amount of memory and dont be as fast as possible.
    Its non comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>

struct MinMax {
    int min;
    int max;
};

void printArray(int* array, const int size) {

    printf("[");

    for (int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);

    printf("%d]\n", array[size - 1]);
}

struct MinMax findMinMax(int* array, const int size) {
    int min = array[0];
    int max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] < min) min = array[i];
        if (array[i] > max) max = array[i];
    }
        
    struct MinMax result;
    result.max = max;
    result.min = min;

    return result;
}

void countSort(int* array, const int size) {

    const struct MinMax mm = findMinMax(array, size);

    const int min = mm.min;
    const int max = mm.max;

    const int range = max - min + 1;

    int* count = (int *) calloc((max - min) + 1, sizeof(int));
    int* output = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++) 
        count[array[i] - min]++;

    for (int i = 1; i < range; i++) 
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i] - min] - 1] = array[i];
        count[array[i] - min]--;
    }
    
    for (int i = 0; i < size; i++)
        array[i] = output[i];

    free(count);
    free(output);
}

/*  Simple version of count sort: (only for positive numbers sort)

    void countSort(int* array, const int size) {

        int greaterElement = findGreater(array, size);

        int* count = (int *) calloc(greaterElement + 1, sizeof(int));

        for (int i = 0; i < size; i++) count[array[i]]++;

        int index = 0;

        for (int i = 0; i <= greaterElement; i++)
            for (int j = 0; j < count[i]; j++)
                array[index++] = i;
        
        free(count);
    }

*/

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    countSort(array, size);

    printf("Array after sort: ");
    printArray(array, size);

    return 0;
}