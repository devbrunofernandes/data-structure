#include <stdio.h>

// recursion is a function that calls itself
// this is a recursive function
void fun(int n) {
    if (n > 0) { // this condicional is the base case of recursive function. every recursive function must have a base case to know when stop recalling.
        printf("%d ", n); // printf is being called before the recursive function call. this will be executed in calling/ascending time.
        fun(n - 1); // recursive call. operations in this recursion call line will be done after the return of the function.
        // if instructions are here after recursive call. this will be executed in returning/descending time.
    }
}

int main() {
    int x = 50000;
    fun(x);

    return 0;
}