#include <stdio.h>

const int LENGTH = 5;

int main()
{
    // declaration of integer array of size five. syntax:(data type) ('array name')[('length of the array')];
    /* declaration and initialization methods:
    int A[5]; not initialized, this array will have garbage values at this moment
    int A[] = {2,4,6,8,10}; declaration with initialization. the size of array will be the number of elements initialized
    int A[5] = {0}; initialization with zeros in all index of array
    int A[5] = {2, 4}; initialize with just the first elements. the others will be initialize as zero
    */
    int A[LENGTH] = {2, 4, 6, 8, 10};
    printf("%d\n", A[2]); // accessing one value in the array by index inside brackets
    
    for (int i = 0; i < LENGTH; i++)
        printf("%d element: %d\n", i+1, A[i]); // iterating over all array values and printing
}