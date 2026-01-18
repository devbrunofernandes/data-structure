/*
    Time complexity: O(n + k) - k is the range between min and max value in list.
    Space complexity: O(n + k) - high memory use.
    Is NOT Adaptive - can NOT easily sort a almost sorted list.
    Is Stable - Can keep the current order of same weight elements.

    Didatic implementation. Ineficient for integers (use Count Sort).
    Its non comparative sorting - can only sort numbers.
*/

#include <stdlib.h>
#include <stdio.h>

struct MinMax {
    int min;
    int max;
};

struct Node {
    int value;
    struct Node* next;
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

void binSort(int* array, const int size) {

    const struct MinMax mm = findMinMax(array, size);

    const int min = mm.min;
    const int max = mm.max;

    const int range = max - min + 1;

    struct Node** bins = (struct Node**) calloc((max - min) + 1, sizeof(struct Node*));

    for (int i = 0; i < size; i++) {

        struct Node* bin = bins[array[i] - min];

        struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
        newNode->value = array[i];
        newNode->next = NULL;

        while (bin && bin->next) bin = bin->next;

        if (!bin)
            bins[array[i] - min] = newNode;
        else
            bin->next = newNode;
    }
    
    int index = 0;

    for (int i = 0; i < range; i++) {

        while (bins[i]) {
            struct Node* bin = bins[i];
            
            array[index++] = bin->value;

            bins[i] = bin->next;

            free(bin);
        }
    }

    free(bins);
}

int main() {
    const int size = 11;
    int array[] = {10, 2, 6, 5, 1, 9, 12, 41, 4, 10, -5};

    printf("Array before sort: ");
    printArray(array, size);

    binSort(array, size);

    printf("Array after sort:  ");
    printArray(array, size);

    return 0;
}