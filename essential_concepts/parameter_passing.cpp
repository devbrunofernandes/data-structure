#include <iostream>

using namespace std;

void swapByValue(int a, int b);
void swapByAddress(int *a, int *b);
void swapByReference(int &a, int &b);

void swapByValue(int a, int b)
{ // the variables of a funtion only exist in memory during the function execution. 
    int temp;             // the function cannot access variable from another function.
    temp = a;
    a = b;
    b = temp;
} // useful with functions that return values.y

void swapByAddress(int *a, int *b) // use pointer as parameters.
{             
    int temp;
    temp = *a;  // must use deref to access the real values that the pointer is poiting to.
    *a = *b;
    *b = temp;
}

// ONLY AVALIABLE IN C++.
void swapByReference(int &a, int &b) // use references as parameters. NEED BE USED WITH CAUTION.
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

int main() 
{
    int x, y;
    x = 10;
    y = 20;

    swapByValue(x, y); // this is passing parameters by value, passing directly the 'x' and 'y' variables value.
    printf("Passing parameters by value:\n");
    printf("X: %d\nY: %d\n", x, y); // the values are not swapped because of the variables scope.

    x = 10;
    y = 20;

    swapByAddress(&x, &y); // this is passing parameters by address, passing the address of 'x' and 'y' variables.
    printf("Passing parameters by address:\n");
    printf("X: %d\nY: %d\n", x, y); // the values are swapped because the function now receive the pointers and modify the real values.

    x = 10;
    y = 20;

    // ONLY AVALIABLE IN C++.
    swapByReference(x, y); // this is passing parameters by reference, passing directly the 'x' and 'y' values but the function will create references to this values.
    printf("Passing parameters by reference:\n");
    printf("X: %d\nY: %d\n", x, y); // the values are swapped because the function now create references or nicknames to the real values and modify them.

    return 0;
}