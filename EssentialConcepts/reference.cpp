#include <iostream>

using namespace std;

// use of reference in variable declaration.
// only avaliable in C++.

int main() {
    int defaultVariable;
    int &referenceVariable = defaultVariable; // creates an nickname for a variable using reference operator in declaration.

    defaultVariable = 10;
    printf("Printing the reference variable: %d\n", referenceVariable);

    return 0;
}